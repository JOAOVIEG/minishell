/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/08 14:32:42 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_simple_cmds(t_node *node)
{	
	no_cmd_file_redir(node);
	if (node->cmd->arg[0] == NULL)
		return ;
	else if (is_builtin(node) == 1)
		exec_builtin(node);
	else if (is_builtin(node) == 0)
		return ;
	else if (is_builtin(node) == 2)
		exec_cmd(node);
}

void	ft_exec_piped(t_node *node)
{
	int		pipe_end[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(1);
	}
	heredoc_check(node->left);
	left_pid = fork();
	left_node_process(node, pipe_end, left_pid);
	heredoc_check(node->right);
	right_pid = fork();
	right_node_process(node, pipe_end, right_pid);
	parent_pipe_exec_control(node, pipe_end, left_pid, right_pid);
}

void	heredoc_check(t_node *node)
{
	if (node->cmd && node->cmd->heredoc)
	{
		node->fd_in = heredoc(node);
		if (node->fd_in < 0)
			exit_shell(1);
	}
}

void	ft_execute(t_node *node)
{
	if (node->type == TYPE_COMMAND)
		ft_simple_cmds(node);
	if (node->type == TYPE_PIPE)
		ft_exec_piped(node);
}
