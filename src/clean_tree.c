/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/15 14:58:02 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

void	free_tree_cmd(t_cmd *cmd)
{
	if (cmd->arg)
		ft_free_str_array(cmd->arg);
	// if (cmd->cmd_path)
	// 	ft_free_str_array(cmd->cmd_path);
	// if (cmd->path)
	// 	free(cmd->path);
	if (cmd->valid_cmd_path)
		free(cmd->valid_cmd_path);
	free(cmd);
	cmd = NULL;
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
    free(*tree_node);
    *tree_node = NULL;
}

void	reset_tree(void)
{
	if (shell()->node)
		free_tree_node(&shell()->node);
}