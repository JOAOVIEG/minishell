/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:15:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/20 15:51:34 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_tree_cmd(t_cmd *cmd)
{
	if (cmd->arg)
		ft_free_str_array(cmd->arg);
	if (cmd->cmd_path)
		ft_free_str_array(cmd->cmd_path);
	/*if (cmd->path)
		free(cmd->path);*/
	if (cmd->valid_cmd_path)
		free(cmd->valid_cmd_path);
	free(cmd);
}

void	free_tree_node(t_node **tree_node)
{
    if ((*tree_node)->cmd)
    {
        free_tree_cmd((*tree_node)->cmd);
        (*tree_node)->cmd = NULL;
    }
    if ((*tree_node)->left)
    {
        free_tree_node(&(*tree_node)->left);
        (*tree_node)->left = NULL;
    }
    if ((*tree_node)->right)
    {
        free_tree_node(&(*tree_node)->right);
        (*tree_node)->right = NULL;
    }
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
	if (shell()->node)
		free_tree_node(&shell()->node);
}