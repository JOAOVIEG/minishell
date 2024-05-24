/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_redir_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:40:08 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:42:46 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_redir_tree(t_shell *shell)
{
	t_buffer		buffer;
	t_lst_tokens	*current;
	t_node			*tree;

	init_buffer(&buffer);
	current = shell->parser->tokens;
	while (current != NULL)
		build_token_queue(&current, &buffer);
	tree = new_redir_tree_node(buffer);
	clean_buffer(&buffer);
	shell->node = tree;
}

void	build_redir_pipe_tree(t_shell *shell)
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
