/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:06:00 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/04 15:49:40 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_exec_control(t_node *node, pid_t pid, char **env)
{
	(void)env;
	parent_control(node, pid);
	// free_c_env(env);
	// if (node->cmd->valid_cmd_path)
	// 	free_paths(node);
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
	if (node->cmd->path)
		free(node->cmd->path);
	// This part is commented out because is causing a double free error
}

// Parser changes
void	child_exec_process(t_node *node, char **env)
{
	handle_signal(SIG_CHILD);
	redirections(node->fd_in, node->fd_out);
	close_fds(node->fd_in, node->fd_out);
	if (execve(node->cmd->valid_cmd_path, node->cmd->arg, env) < 0)
	{
		free_paths(node);
		if (env)
			free_c_env(env);
		exit_shell(shell()->status);
	}
	child_control(node);
	// free_paths(node);
	handle_signal(SIG_DEFAULT);
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
	{
		child_exec_process(node, env);
		// free_c_env(env);
		// if (node->cmd->cmd_path)
		// 	free_cmd_paths(node->cmd->cmd_path);
	}
	else
		parent_exec_control(node, pid, env);
}

void	status_error(char *what, char *message, int fd)
{
	char	*str;
	char	*temp;
	char	*m;
		
	temp = ft_strjoin(what, ": ");
	str = ft_strjoin(temp, message);
	free(temp);
	m = ft_strjoin("bash: ", str);
	free(str);
	ft_putendl_fd(m, fd);
	free(m);
}
