/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/03 17:57:07 by joaocard         ###   ########.fr       */
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
	else if (is_builtin(node) == 2)
		exec_cmd(node);
}

void	ft_exec_piped(t_node *node)
{
	int		pipe_end[2];
	int		l_status;
	int		r_status;
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(EXIT_FAILURE);
	}
	if (shell()->heredoced == false && ((reads_from_stdin(node->left) == 1 || \
			reads_from_stdin(node->right) == 1) || \
			(node->right->type == TYPE_PIPE && \
			(reads_from_stdin(node->right->left) == 1 \
			|| reads_from_stdin(node->right->right) == 1))))
	{
		left_pid = fork();
		left_node_process(node, pipe_end, left_pid);
		right_pid = fork();
		right_node_process(node, pipe_end, right_pid);
		parent_pipe_exec_control(node, pipe_end, right_pid, left_pid);
	}
	else if (shell()->heredoced == true && (reads_from_stdin(node->left) == 1 || \
			reads_from_stdin(node->right) == 1))
	{
		left_pid = fork();
		left_node_process(node, pipe_end, left_pid);
		right_pid = fork();
		right_node_process(node, pipe_end, right_pid);
		parent_pipe_exec_control(node, pipe_end, right_pid, left_pid);	
	}
	else
	{
		left_pid = fork();
		left_node_process(node, pipe_end, left_pid);
		if (left_pid > 0)
		{
			close(pipe_end[1]);
			close(pipe_end[0]);
			waitpid(left_pid, &l_status, 0);
			if (WIFEXITED(l_status))
				shell()->status = WEXITSTATUS(l_status);
		}
		right_pid = fork();
		right_node_process(node, pipe_end, right_pid);
		if (right_pid > 0)
		{
			close(pipe_end[0]);
			close(pipe_end[1]);
			waitpid(right_pid, &r_status, 0);
			if (WIFEXITED(r_status))
				shell()->status = WEXITSTATUS(r_status);
		}
	}
}

void	heredoc_check(t_node *node, int i)
{
	if (node->cmd && node->cmd->heredoc)
	{
		node->fd_in = heredoc(node, i);
		if (node->fd_in < 0)
		{
			printf("erro\n");
			shell()->status = EXIT_FAILURE;
			exit_shell(shell()->status);
		}
	}
}

void	ft_execute(t_node *node)
{
	if (node->type == TYPE_PIPE)
		ft_exec_piped(node);
	else if (node->type == TYPE_COMMAND)
		ft_simple_cmds(node);
}

void	heredoc_builtin_here(t_node *node, pid_t pid, int i)
{
	if (pid < 0)
	{
		perror("Error forking");
		shell()->status = EXIT_FAILURE;
		exit_shell(shell()->status);
	}
	else if (pid == 0)
		builtin_heredoc_child(node, i);
	else
		parent_control(node, pid);
}
