/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:50 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/01 18:41:29 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	is_builtin(t_node *node)
{
	char *cmd;

	cmd = node->cmd->arg[0];
    if (cmd == NULL)
	{
		if (node->cmd->file && node->cmd->file[0] != NULL)
		{
			if (ft_strcmp(node->cmd->file[0], ">") == 0)
				open(node->cmd->file[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		return (0);
	}
		
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
	char **cmd;
	pid_t	pid;
	int		status;
	int		i;

	if (node->cmd->file && *node->cmd->file != NULL)
	{
		i = 0;
		while (node->cmd->file && node->cmd->file[i] != NULL)
		{
			node->fd_in = dup(STDIN_FILENO);
			node->fd_out = dup(STDOUT_FILENO);
			if (ft_strchr(node->cmd->file[i], '<') != NULL)
			{
				i++;
				close(node->fd_in);
				node->fd_in = open(node->cmd->file[i], O_RDONLY);
				if (node->fd_in < 0)
				{
					perror("Error at fd_in");
					exit_shell(EXIT_FAILURE);
				}
				i++;
			}
			else if (ft_strchr(node->cmd->file[i], '>') != NULL)
			{
				i++;
				close(node->fd_out);
				node->fd_out = open(node->cmd->file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (node->fd_out < 0)
				{
					perror("Error at fd_out");
					exit_shell(EXIT_FAILURE);
				}
				i++;
			}
			else
				i++;
		}
		pid = fork();
		if (pid < 0)
		{
			perror("Error forking");
			exit_shell(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			redirections(node->fd_in, node->fd_out);
			cmd = node->cmd->arg;
			if (ft_strcmp(cmd[0], "cd") == 0)
				cd (cmd[1]);
			if (ft_strcmp(cmd[0], "pwd") == 0)
				pwd();
			if (ft_strcmp(cmd[0], "echo") == 0)
				echo(cmd);
			if (ft_strcmp(cmd[0], "export") == 0)
				export(cmd);
			if (ft_strcmp(cmd[0], "exit") == 0)
				exit_shell(0);
			if (ft_strcmp(cmd[0], "unset") == 0)
				unset(cmd);
			if (ft_strcmp(cmd[0], "env") == 0)
				env();
			close_fds(node->fd_in, node->fd_out);
			close(node->fd_in);
			close(node->fd_out);
			exit_shell(EXIT_SUCCESS);
		}
		else
		{
			close_fds(node->fd_in, node->fd_out);
			close(node->fd_in);
			close(node->fd_out);
			waitpid(pid, &status, 0);
		}
		
	}
	else
	{
		cmd = node->cmd->arg;
		if (ft_strcmp(cmd[0], "cd") == 0)
			cd (cmd[1]);
		if (ft_strcmp(cmd[0], "pwd") == 0)
			pwd();
		if (ft_strcmp(cmd[0], "echo") == 0)
			echo(cmd);
		if (ft_strcmp(cmd[0], "export") == 0)
			export(cmd);
		if (ft_strcmp(cmd[0], "exit") == 0)
			exit_shell(0);
		if (ft_strcmp(cmd[0], "unset") == 0)
			unset(cmd);
		if (ft_strcmp(cmd[0], "env") == 0)
			env();
	}
}

void	exec_cmd(t_node *node)
{
	char	**env;
	int		status;
	pid_t	pid;
	int		i;

	i = 0;
	node->fd_in = dup(STDIN_FILENO);
	node->fd_out = dup(STDOUT_FILENO);
	env = env_list_to_arr();
	check_path(env, node);
	// if (node->cmd->file && node->cmd->file[i])
	// 	printf("%s\n", node->cmd->file[i]);
	// else
	// 	printf("file is empty\n");
	while (node->cmd->file && node->cmd->file[i] != NULL)
	{
		if (ft_strchr(node->cmd->file[i], '<') != NULL)
		{
			i++;
			close(node->fd_in);
			node->fd_in = open(node->cmd->file[i], O_RDONLY);
			if (node->fd_in < 0)
			{
				perror("Error at fd_in");
				free_c_env(env);
				exit_shell(EXIT_FAILURE);
			}
			i++;
		}
		else if (ft_strchr(node->cmd->file[i], '>') != NULL)
		{
			i++;
			close(node->fd_out);
			node->fd_out = open(node->cmd->file[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (node->fd_out < 0)
			{
				perror("Error at fd_out");
				free_c_env(env);
				exit_shell(EXIT_FAILURE);
			}
			i++;
		}
		else
			i++;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error forking");
		free_c_env(env);
		exit_shell(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if ((node->cmd->valid_cmd_path = get_cmd(node->cmd->cmd_path, \
				node->cmd->arg[0])) == NULL)
		{
			free_c_env(env);
			if (node->cmd->valid_cmd_path)
			{
				free(node->cmd->valid_cmd_path);
				node->cmd->valid_cmd_path = NULL;
			}
			if (node->cmd->cmd_path)
				free_cmd_paths(node->cmd->cmd_path);
			exit_shell(EXIT_FAILURE);
		}
		redirections(node->fd_in, node->fd_out);
		close_fds(node->fd_in, node->fd_out);
		if (execve(node->cmd->valid_cmd_path, node->cmd->arg, env) < 0)
		{
			free_c_env(env);
			if (node->cmd->valid_cmd_path)
			{
				free(node->cmd->valid_cmd_path);
				node->cmd->valid_cmd_path = NULL;
			}
			if (node->cmd->cmd_path)
				free_cmd_paths(node->cmd->cmd_path);
			exit_shell(EXIT_FAILURE);
		}
		close(node->fd_in);
		close(node->fd_out);
		exit_shell(EXIT_SUCCESS);
	}
	else
	{
		close_fds(node->fd_in, node->fd_out);
		close(node->fd_in);
		close(node->fd_out);
		waitpid(pid, &status, 0);
		free_c_env(env);
		if (node->cmd->cmd_path)
			free_cmd_paths(node->cmd->cmd_path);
		if (node->cmd->valid_cmd_path)
		{
			free(node->cmd->valid_cmd_path);
			node->cmd->valid_cmd_path = NULL;
		}
	}
}
