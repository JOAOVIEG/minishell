/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:32:30 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/18 21:36:09 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_pipe_exec_control(t_node *node, int pipe_end[2], \
					pid_t right_pid, pid_t left_pid)
{
	int		r_status;
	int		l_status;

	close(pipe_end[0]);
	if (node->right->fd_in)
		close(node->right->fd_in);
	close(pipe_end[1]);
	if (node->left->fd_out)
		close(node->left->fd_out);
	if (node->left->cmd->heredoc)
		close(node->left->fd_in);
	waitpid(left_pid, &l_status, 0);
	waitpid(right_pid, &r_status, 0);
	if (WIFEXITED(l_status))
		shell()->status = WEXITSTATUS(l_status);
	if (WIFEXITED(r_status))
		shell()->status = WEXITSTATUS(r_status);
}

void	execute_right_node(t_node *node, int pipe_end[2])
{
	close(node->right->fd_in);
	node->right->fd_in = pipe_end[0];
	dup2(node->right->fd_in, STDIN_FILENO);
	close(pipe_end[1]);
	ft_execute(node->right);
	close(node->right->fd_in);
	close(pipe_end[0]);
	exit_shell(shell()->status);
}

void	execute_left_node(t_node *node, int pipe_end[2])
{
	close(pipe_end[0]);
	node->left->fd_out = pipe_end[1];
	dup2(node->left->fd_out, STDOUT_FILENO);
	ft_execute(node->left);
	close(pipe_end[1]);
	exit_shell(shell()->status);
	
}

void	right_node_process(t_node *node, int pipe_end[2], pid_t right_pid)
{
	if (right_pid < 0)
	{
		perror("right fork failed");
		exit_shell(EXIT_FAILURE);
	}
	else if (right_pid == 0)
	{
		shell()->status = EXIT_SUCCESS;
		assign_fds(node->right);
		execute_right_node(node, pipe_end);
	}
}

void	left_node_process(t_node *node, int pipe_end[2], pid_t left_pid)
{
	if (left_pid < 0)
	{
		perror("left fork failed");
		exit_shell(2);
	}
	else if (left_pid == 0)
	{
		shell()->status = EXIT_SUCCESS;
		execute_left_node(node, pipe_end);
	}
}
