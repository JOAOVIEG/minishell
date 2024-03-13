/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:15:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/13 19:47:07 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_tree_cmd(t_cmd *cmd)
{
	if (cmd->arg)
		ft_free_str_array(cmd->arg);
	if (cmd->valid_cmd_path)
		free(cmd->valid_cmd_path);
	if (cmd->file)
		ft_free_str_array(cmd->file);
	if (cmd->heredoc)
		ft_free_str_array(cmd->heredoc);
	free(cmd);
	cmd = NULL;
}

void	free_tree_node(t_node **tree_node)
{
	if ((*tree_node)->cmd)
		free_tree_cmd((*tree_node)->cmd);
	if ((*tree_node)->left)
		free_tree_node(&(*tree_node)->left);
	if ((*tree_node)->right)
		free_tree_node(&(*tree_node)->right);
	if ((*tree_node)->fd_in)
	{
		close((*tree_node)->fd_in);
		(*tree_node)->fd_in = 0;
	}
	if ((*tree_node)->fd_out)
	{
		close((*tree_node)->fd_out);
		(*tree_node)->fd_out = 0;
	}
	free(*tree_node);
	*tree_node = NULL;
}

void	reset_tree(void)
{
	// shell()->status = EXIT_SUCCESS;
	if (shell()->node)
		free_tree_node(&shell()->node);
}
