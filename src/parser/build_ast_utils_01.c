/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:12:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:58:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_node(t_token_type type, t_cmd *cmd, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)ft_calloc_memory(1, sizeof(t_node));
	node->type = type;
	node->cmd = cmd;
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*new_redir_tree_node(t_buffer buffer)
{
	t_node	*new_node;

	new_node = new_tree_node(buffer.cmds.head);
	new_node->cmd->file = get_redir_files(buffer.redir_files.head);
	new_node->cmd->heredoc = get_redir_files(buffer.heredocs.head);
	return (new_node);
}

t_node	*create_node_and_update_redir_pipe_tree(t_node **tree_root,
		t_node **rightmost_node, t_buffer buffer)
{
	t_node	*new_node;

	new_node = new_redir_tree_node(buffer);
	if (!new_node)
		return (NULL);
	if (!*tree_root)
	{
		*tree_root = new_node;
		*rightmost_node = new_node;
	}
	else
		update_tree_root(tree_root, rightmost_node,
			create_pipe_node(*rightmost_node, new_node));
	return (new_node);
}

t_lst_tokens	*get_cmd_list(t_lst_tokens **current, t_lst_tokens **cmd_tokens,
		t_lst_tokens **tail)
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
	if (!current)
		return (NULL);
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
