/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:50 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/13 20:11:49 by joaocard         ###   ########.fr       */
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
					node->fd_in = heredoc(node);
				child_control(node);
			}
		}
		else
			parent_control(node, pid);
	}
	run_process(node);
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
				if (node->cmd->heredoc)
				{
					if (!node->fd_in)
						node->fd_in = heredoc(node);
					close(node->fd_out);
					exit_shell(shell()->status);
				}
			}
			else
				parent_control(node, pid1);
	}
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
		exit_shell(shell()->status);
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
