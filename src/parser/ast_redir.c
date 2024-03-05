/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:23:16 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/05 16:28:37 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_token_queue(t_token_queue *queue)
{
	queue->head = NULL;
	queue->tail = NULL;
}

void	clean_token_queue(t_token_queue *queue)
{
	t_lst_tokens	*current;
	t_lst_tokens	*next;

	current = queue->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	queue->head = NULL;
	queue->tail = NULL;
}

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

t_node	*new_redir_tree_node(t_token_queue cmds, t_token_queue redir_files)
{
	t_node	*new_node;

	new_node = new_tree_node(cmds.head);
	new_node->cmd->file = get_redir_files(redir_files.head);
	return (new_node);
}

t_node	*new_heredoc_node(t_token_queue cmds, t_token_queue heredocs, t_token_queue redir_files)
{
	t_node	*new_node;

	new_node = new_tree_node(cmds.head);
	new_node->cmd->heredoc = get_redir_files(heredocs.head);
	new_node->cmd->file = get_redir_files(redir_files.head);
	return (new_node);
}

void	build_token_queue(t_lst_tokens **current, t_token_queue *cmds,
		t_token_queue *redir_files)
{
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		if ((*current)->type == TYPE_REDIRECT)
			redir_files->head = get_redir_list(current, &redir_files->head,
					&redir_files->tail);
		else
			cmds->head = get_cmd_list(current, &cmds->head, &cmds->tail);
	}
}

void	build_redir_tree(t_shell *shell)
{
	t_token_queue	cmds;
	t_token_queue	redir_files;
	t_lst_tokens	*current;
	t_node			*tree;

	init_token_queue(&cmds);
	init_token_queue(&redir_files);
	current = shell->parser->tokens;
	while (current != NULL)
		build_token_queue(&current, &cmds, &redir_files);
	tree = new_redir_tree_node(cmds, redir_files);
	clean_token_queue(&cmds);
	clean_token_queue(&redir_files);
	shell->node = tree;
}

t_node	*create_node_and_update_redir_pipe_tree(t_node **tree_root,
		t_node **rightmost_node, t_token_queue cmds, t_token_queue redir_files)
{
	t_node	*new_node;

	new_node = new_redir_tree_node(cmds, redir_files);
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

t_node	*create_node_and_update_heredoc_pipe_tree(t_node **tree_root,
		t_node **rightmost_node, t_token_queue cmds, t_token_queue heredocs, t_token_queue redir_files)
{
	t_node	*new_node;
	
	new_node = new_heredoc_node(cmds, heredocs, redir_files);
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

void	build_redir_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_token_queue	cmds;
	t_token_queue	redir_files;
	t_lst_tokens	*current;

	tree_root = NULL;
	rightmost_node = NULL;
	init_token_queue(&cmds);
	init_token_queue(&redir_files);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_token_queue(&current, &cmds, &redir_files);
		rightmost_node = create_node_and_update_redir_pipe_tree(&tree_root,
				&rightmost_node, cmds, redir_files);
		if (current != NULL)
			current = current->next;
		clean_token_queue(&cmds);
		clean_token_queue(&redir_files);
	}
	shell->node = tree_root;
}

void	build_heredoc_queue(t_lst_tokens **current, t_token_queue *cmds,
		t_token_queue *heredocs)
{
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		if ((*current)->type == TYPE_HEREDOC)
			heredocs->head = get_redir_list(current, &heredocs->head,
					&heredocs->tail);
		else
			cmds->head = get_cmd_list(current, &cmds->head, &cmds->tail);
	}
}

void build_heredoc_redir_queue(t_lst_tokens **current, t_token_queue *cmds,
		t_token_queue *heredocs, t_token_queue *redir_files)
{
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		if ((*current)->type == TYPE_HEREDOC)
			heredocs->head = get_redir_list(current, &heredocs->head,
					&heredocs->tail);
		else if ((*current)->type == TYPE_REDIRECT)
			redir_files->head = get_redir_list(current, &redir_files->head,
					&redir_files->tail);
		else
			cmds->head = get_cmd_list(current, &cmds->head, &cmds->tail);
	}

}


void	build_heredoc_tree(t_shell *shell)
{
	t_node			*tree;
	t_lst_tokens	*current;
	t_token_queue	cmds;
	t_token_queue	heredocs;
	t_token_queue	redir_files;

	tree = NULL;
	init_token_queue(&cmds);
	init_token_queue(&heredocs);
	init_token_queue(&redir_files);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_heredoc_queue(&current, &cmds, &heredocs);
		if (current != NULL)
			current = current->next;
	}
	tree = new_heredoc_node(cmds, heredocs, redir_files);
	clean_token_queue(&cmds);
	clean_token_queue(&heredocs);
	shell->node = tree;
}

void	build_heredoc_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_token_queue	cmds;
	t_token_queue	heredocs;
	t_token_queue	redir_files;
	t_lst_tokens	*current;

	tree_root = NULL;
	rightmost_node = NULL;
	init_token_queue(&cmds);
	init_token_queue(&heredocs);
	init_token_queue(&redir_files);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_heredoc_queue(&current, &cmds, &heredocs);
		rightmost_node = create_node_and_update_heredoc_pipe_tree(&tree_root,
				&rightmost_node, cmds, heredocs, redir_files);
		if (current != NULL)
			current = current->next;
		clean_token_queue(&cmds);
		clean_token_queue(&heredocs);
	}
	shell->node = tree_root;
}


void	build_heredoc_redir_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_token_queue	cmds;
	t_token_queue	heredocs;
	t_token_queue	redir_files;
	t_lst_tokens	*current;

	tree_root = NULL;
	rightmost_node = NULL;
	init_token_queue(&cmds);
	init_token_queue(&heredocs);
	init_token_queue(&redir_files);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_heredoc_redir_queue(&current, &cmds, &heredocs, &redir_files);
		rightmost_node = create_node_and_update_heredoc_pipe_tree(&tree_root,
				&rightmost_node, cmds, heredocs, redir_files);
		if (current != NULL)
			current = current->next;
		clean_token_queue(&cmds);
		clean_token_queue(&heredocs);
		clean_token_queue(&redir_files);
	}
	shell->node = tree_root;
}
