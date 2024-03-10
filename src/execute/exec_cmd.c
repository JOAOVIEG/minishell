/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:06:00 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/10 16:34:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_exec_control(t_node *node, pid_t pid, char **env)
{
	parent_control(node, pid);
	free_c_env(env);
	free_paths(node);
}

void	free_paths(t_node *node)
{
	if (node->cmd->cmd_path)
		free_cmd_paths(node->cmd->cmd_path);
	if (node->cmd->valid_cmd_path)
	{
		free(node->cmd->valid_cmd_path);
		node->cmd->valid_cmd_path = NULL;
	}
}

void	child_exec_process(t_node *node, char **env)
{
	if (strcmp(node->cmd->arg[0], ".") == 0 || \
						strcmp(node->cmd->arg[0], "..") == 0)
	{
		printf("%s: command not found\n", node->cmd->arg[0]);
		exit_shell(127);
	}
	if (input_is_dir(node) == 1)
		exit_shell(126);
	node->cmd->valid_cmd_path = get_cmd(node->cmd->cmd_path, \
		node->cmd->arg[0]);
	if (node->cmd->valid_cmd_path == NULL)
	{
		free_c_env(env);
		free_paths(node);
		exit_shell(shell()->status);
	}
	redirections(node->fd_in, node->fd_out);
	close_fds(node->fd_in, node->fd_out);
	if (execve(node->cmd->valid_cmd_path, node->cmd->arg, env) < 0)
	{
		free_c_env(env);
		free_paths(node);
		exit_shell(126);
	}
	child_control(node);
}

void	run_path_process(t_node *node, pid_t pid, char **env)
{
	if (pid < 0)
	{
		perror("Error forking");
		free_c_env(env);
		shell()->status = EXIT_FAILURE;
		exit_shell(shell()->status);
	}
	else if (pid == 0)
		child_exec_process(node, env);
	else
		parent_exec_control(node, pid, env);
}
