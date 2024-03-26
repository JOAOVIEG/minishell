/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/26 16:43:53 by wiferrei         ###   ########.fr       */
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

/* void	ft_exec_piped(t_node *node)
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
	if ((reads_from_stdin(node->left) == 1 || \
			reads_from_stdin(node->right) == 1) && check_heredoc(node) == 0)
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
} */

void	ft_exec_piped(t_node *node)
{
	int		pipe_end[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(EXIT_FAILURE);
	}
	left_pid = fork();
	if (left_pid == 0)
	{
		// This is the left child process.
		// Close the read end of the pipe.
		close(pipe_end[0]);
		// Redirect stdout to the write end of the pipe.
		dup2(pipe_end[1], STDOUT_FILENO);
		close(pipe_end[1]);
		// Execute the left command.
		ft_execute(node->left);
		exit(EXIT_SUCCESS);
	}
	right_pid = fork();
	if (right_pid == 0)
	{
		// This is the right child process.
		// Close the write end of the pipe.
		close(pipe_end[1]);
		// Redirect stdin to the read end of the pipe.
		dup2(pipe_end[0], STDIN_FILENO);
		close(pipe_end[0]);
		// Execute the right command.
		ft_execute(node->right);
		exit(EXIT_SUCCESS);
	}
	// This is the parent process.
	// Close both ends of the pipe.
	close(pipe_end[0]);
	close(pipe_end[1]);
	// Wait for both child processes to finish.
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
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
