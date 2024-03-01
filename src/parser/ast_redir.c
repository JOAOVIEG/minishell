/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:23:16 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/01 17:44:47 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_back(t_lst_tokens **current, t_lst_tokens **cmd_tokens,
		t_lst_tokens **tail)
{
	t_lst_tokens	*new_token;

	new_token = ft_calloc_memory(1, sizeof(t_lst_tokens));
	new_token->data = ft_strdup((*current)->data);
	new_token->type = (*current)->type;
	new_token->next = NULL;
	lst_tokenadd_back(cmd_tokens, tail, new_token);
	*current = (*current)->next;
}

t_lst_tokens	*get_redir_list(t_lst_tokens **current,
		t_lst_tokens **cmd_tokens, t_lst_tokens **tail)
{
	add_token_back(current, cmd_tokens, tail);
	if (*current != NULL)
	{
		add_token_back(current, cmd_tokens, tail);
	}
	return (*cmd_tokens);
}

t_lst_tokens	*get_cmd_list(t_lst_tokens **current,
		t_lst_tokens **cmd_tokens, t_lst_tokens **tail)
{
	if (*current != NULL && (*current)->type != TYPE_REDIRECT)
		add_token_back(current, cmd_tokens, tail);
	else
		*current = (*current)->next;
	return (*cmd_tokens);
}

char	**get_redir_files(t_lst_tokens *tokens)
{
	int				i;
	t_lst_tokens	*current;
	char			**file;

	i = 0;
	current = tokens;
	file = (char **)ft_calloc_memory(lst_token_size(tokens) + 1,
			sizeof(char *));
	while (current != NULL)
	{
		file[i] = ft_strdup(current->data);
		current = current->next;
		i++;
	}
	file[i] = NULL;
	return (file);
}

void	build_redir_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_token_queue	cmds;
	t_token_queue	redir_files;
	t_lst_tokens	*current;

	cmds.head = NULL;
	cmds.tail = NULL;
	redir_files.head = NULL;
	redir_files.tail = NULL;
	current = shell->parser->tokens;
	while (current != NULL)
	{
		if (current->type == TYPE_REDIRECT)
			redir_files.head = get_redir_list(&current, &redir_files.head,
					&redir_files.tail);
		else
			cmds.head = get_cmd_list(&current, &cmds.head,
					&cmds.tail);
	}
	tree_root = new_tree_node(cmds.head);
	tree_root->cmd->file = get_redir_files(redir_files.head);
	free_lst_tokens(cmds.head);
	free_lst_tokens(redir_files.head);
	shell->node = tree_root;
}
