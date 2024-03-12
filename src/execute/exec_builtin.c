/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:49:54 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/12 13:36:09 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_builtin(t_node *node)
{
	char	**cmd;

	cmd = node->cmd->arg;
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		if (!cmd[2])
			cd(cmd[1]);
		else
		{
			status_error(cmd[0], "too many arguments", STDERR_FILENO);
			shell()->status = EXIT_FAILURE;
		}
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo(cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		export(cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit_shell(EXIT_SUCCESS);
	if (ft_strcmp(cmd[0], "unset") == 0)
		unset(cmd);
	if (ft_strcmp(cmd[0], "env") == 0)
		env();
}

void	parent_control(t_node *node, pid_t pid)
{
	int	status;

	handle_signal(SIG_PARENT); // keep this line
	close_fds(node->fd_in, node->fd_out);
	close(node->fd_in);
	close(node->fd_out);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell()->status = WEXITSTATUS(status);
	handle_signal(SIG_DEFAULT); // keep this line
}

void	child_control(t_node *node)
{
	close(node->fd_in);
	close(node->fd_out);
	exit_shell(shell()->status);
}

void	run_process(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error forking");
		shell()->status = EXIT_FAILURE;
		exit_shell(shell()->status);
	}
	else if (pid == 0)
	{
		redirections(node->fd_in, node->fd_out);
		run_builtin(node);
		child_control(node);
	}
	else
		parent_control(node, pid);
}

int	open_file_to(t_node *node, int i)
{
	close(node->fd_out);
	node->fd_out = open(node->cmd->file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (node->fd_out < 0)
	{
		status_error(node->cmd->file[1], " permission denied", STDERR_FILENO);
		shell()->status = 126;
	}
	return (node->fd_out);
}
