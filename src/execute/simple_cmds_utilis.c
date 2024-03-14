/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:50 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/14 16:57:45 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_node *node)
{
	char	*cmd;

	cmd = node->cmd->arg[0];
	if (ft_strcmp(cmd, "cd") == 0 || \
			ft_strcmp(cmd, "pwd") == 0 || \
			ft_strcmp(cmd, "echo") == 0 || \
			ft_strcmp(cmd, "export") == 0 || \
			ft_strcmp(cmd, "unset") == 0 || \
			ft_strcmp(cmd, "env") == 0 || \
			ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (2);
}

void	exec_builtin(t_node *node)
{
	pid_t	pid;
	// pid_t	pid1;
	int		i;

	if (node->cmd->heredoc)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Error forking");
			shell()->status = EXIT_FAILURE;
			exit_shell(shell()->status);
		}
		else if (pid == 0)
		{
			if (node->cmd->heredoc)
			{
				if (!node->fd_in)
					heredoc_check(node);
				child_control(node);
			}
		}
		else
			parent_control(node, pid);
	}
	if (node->cmd->file && *node->cmd->file != NULL)
	{
		i = 0;
		while (node->cmd->file[i] != NULL)
		{
			if (ft_strncmp(node->cmd->file[i], "<", 1) == 0)
				assign_fds(node);
			handle_file_redir(node, i);
			i++;
		}
		if (shell()->status != EXIT_SUCCESS)
			return ;
	}
	// Save the original file descriptors
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stdin = dup(STDIN_FILENO);

	redirections(node->fd_in, node->fd_out);
	run_builtin(node);

	// Restore the original file descriptors
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);

	// Close the saved file descriptors
	close(saved_stdout);
	close(saved_stdin);
}

void	exec_cmd(t_node *node)
{
	char	**env;
	pid_t	pid;
	pid_t	pid1;
	int	i;

	i = 0;
	env = env_list_to_arr();
	check_path(env, node);
	if (node->cmd->heredoc && !node->fd_in)
	{
		pid1 = fork();
			if (pid1 < 0)
			{
				perror("Error forking");
				shell()->status = EXIT_FAILURE;
				exit_shell(shell()->status);
			}
			else if (pid1 == 0)
			{
				heredoc_check(node);
				while (node->cmd->file && node->cmd->file[i] != NULL)
				{
					handle_file_redir(node, i);
					i++;
				}
				if (ft_strcmp(node->cmd->arg[0], ".") == 0
						|| ft_strcmp(node->cmd->arg[0], "..") == 0)
				{
					free_c_env(env);
					shell()->status = 127;
					status_error(node->cmd->arg[0], "command not found", STDERR_FILENO);
					// exit_shell(shell()->status);
				}
				if (input_is_dir(node, env) == 1)
					exit_shell(1);
				node->cmd->valid_cmd_path = get_cmd(node->cmd->cmd_path, node->cmd->arg[0]);
				if (node->cmd->valid_cmd_path == NULL)
				{
					free_c_env(env);
					shell()->status = 127;
					status_error(node->cmd->arg[0], "command not found", STDERR_FILENO);
					return ;
				}
				pid = fork();
				assign_fds(node);
				run_path_process(node, pid, env);
				exit_shell(shell()->status);
			}
			else
			{
				parent_control(node, pid1);
			}
	}
	else
	{
		while (node->cmd->file && node->cmd->file[i] != NULL)
		{
			handle_file_redir(node, i);
			if (shell()->status != EXIT_SUCCESS)
				return ;
			i++;
		}
		if (ft_strcmp(node->cmd->arg[0], ".") == 0
				|| ft_strcmp(node->cmd->arg[0], "..") == 0)
		{
			free_c_env(env);
			shell()->status = 127;
			status_error(node->cmd->arg[0], "command not found", STDERR_FILENO);
			return ;
		}
		if (input_is_dir(node, env) == 1)
			exit_shell(1);
		node->cmd->valid_cmd_path = get_cmd(node->cmd->cmd_path, node->cmd->arg[0]);
		if (node->cmd->valid_cmd_path == NULL)
		{
			free_c_env(env);
			shell()->status = 127;
			status_error(node->cmd->arg[0], "command not found", STDERR_FILENO);
			return ;
		}
		pid = fork();
		assign_fds(node);
		run_path_process(node, pid, env);
	}
}
