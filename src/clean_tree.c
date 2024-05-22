/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:02:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/22 13:22:13 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_tree_cmd(t_cmd *cmd)
{
	if (cmd->arg)
		ft_free_str_array(cmd->arg);
	if (cmd->file)
		ft_free_str_array(cmd->file);
	if (cmd->heredoc)
		ft_free_str_array(cmd->heredoc);
	if (cmd->valid_cmd_path)
	{
		free(cmd->valid_cmd_path);
		cmd->valid_cmd_path = NULL;
	}
	if (cmd->cmd_path)
		ft_free_str_array(cmd->cmd_path);
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
	if (shell()->node)
		free_tree_node(&shell()->node);
}

void	reset_parser_and_tree(void)
{
	if (shell()->lexer)
		reset_lexer(shell()->lexer);
	if (shell()->parser)
		reset_parser(shell()->parser);
	if (shell()->node)
		free_tree_node(&shell()->node);
}
