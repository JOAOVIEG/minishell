/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:06:00 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/13 11:44:52 by wiferrei         ###   ########.fr       */
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
	handle_signal(SIG_CHILD); // keep this line
	int	i;

	i = 0;
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

void	status_error(char *what, char *message, int	fd)
{
	char *str;
	char *temp;

	temp = ft_strjoin(what, ": ");
	str = ft_strjoin(temp, message);
	free(temp);
	ft_putendl_fd(str, fd);
	free(str);
}
