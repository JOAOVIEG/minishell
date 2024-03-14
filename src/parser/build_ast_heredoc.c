/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:35:43 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:38:49 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_heredoc_tree(t_shell *shell)
{
	t_node			*tree;
	t_lst_tokens	*current;
	t_buffer		buffer;

	tree = NULL;
	init_buffer(&buffer);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_token_queue(&current, &buffer);
		if (current != NULL)
			current = current->next;
	}
	tree = new_redir_tree_node(buffer);
	clean_buffer(&buffer);
	shell->node = tree;
}

void	build_heredoc_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_buffer		buffer;
	t_lst_tokens	*current;

	tree_root = NULL;
	rightmost_node = NULL;
	init_buffer(&buffer);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_token_queue(&current, &buffer);
		rightmost_node = create_node_and_update_redir_pipe_tree(&tree_root,
				&rightmost_node, buffer);
		if (current != NULL)
			current = current->next;
		clean_buffer(&buffer);
	}
	shell->node = tree_root;
}

void	build_heredoc_redir_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_buffer		buffer;
	t_lst_tokens	*current;

	tree_root = NULL;
	rightmost_node = NULL;
	init_buffer(&buffer);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_token_queue(&current, &buffer);
		rightmost_node = create_node_and_update_redir_pipe_tree(&tree_root,
				&rightmost_node, buffer);
		if (current != NULL)
			current = current->next;
		clean_buffer(&buffer);
	}
	shell->node = tree_root;
}

void	build_heredoc_redir_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_buffer		buffer;
	t_lst_tokens	*current;

	tree_root = NULL;
	rightmost_node = NULL;
	init_buffer(&buffer);
	current = shell->parser->tokens;
	while (current != NULL)
	{
		build_heredoc_redir_queue(&current, &buffer.cmds, &buffer.heredocs,
			&buffer.redir_files);
		rightmost_node = create_node_and_update_redir_pipe_tree(&tree_root,
				&rightmost_node, buffer);
		if (current != NULL)
			current = current->next;
		clean_buffer(&buffer);
	}
	shell->node = tree_root;
}
