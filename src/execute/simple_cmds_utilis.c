/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:50 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 10:15:29 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_node *node)
{
	char	*cmd;

	cmd = node->cmd->arg[0];
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (2);
}

void	exec_builtin(t_node *node)
{
	int		num_heredocs;
	pid_t	heredoc_pid;
	int		i;
	int		j;
	int		k;
	int saved_stdout;
	int saved_stdin;

	num_heredocs = count_redir(node);
	if (node->cmd->heredoc)
	{
		int k_fd[2];
		if (pipe(k_fd) == -1) 
		{
    		perror("pipe");
    		exit(EXIT_FAILURE);
		}
		k = 1;
		i = 0;
		j = 0;
		heredoc_pid = fork();
		if (heredoc_pid < 0)
		{
			perror("Error forking");
			shell()->status = EXIT_FAILURE;
			exit_shell(shell()->status);
		}
		if (heredoc_pid == 0)
		{
			close(k_fd[0]);
			while (k <= num_heredocs)
			{
				if (node->fd_in)
					close(node->fd_in);
				heredoc_check(node, j);
				write(k_fd[1], &k, sizeof(k));
				close(k_fd[1]);
				j += 2;
				k++;
			}
			close(node->fd_in);
			if (node->fd_out)
				close(node->fd_out);
			if (node->cmd->file && *node->cmd->file)
			{
				i = 0;
				while(node->cmd->file[i])
					handle_file_redir(node, i++);
			}
			redirections(node->fd_in, node->fd_out);
			run_builtin(node);
			child_control(node);
		}
		else
		{
			close(k_fd[1]);
			read(k_fd[0], &k, sizeof(k));
			close(k_fd[0]);
			parent_control(node, heredoc_pid);
			k++;
		}
	}
	else if (node->cmd->file && *node->cmd->file != NULL)
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
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		redirections(node->fd_in, node->fd_out);
		run_builtin(node);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
	else
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		redirections(node->fd_in, node->fd_out);
		run_builtin(node);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
}

void	exec_cmd(t_node *node)
{
	char	**env;
	pid_t	pid;
	pid_t	pid1;
	int		i;
	int		j;
	int		num_heredocs;
	
	i = 0;
	j = 0;
	num_heredocs = shell()->parser->heredoc_count;
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
			while (j <= num_heredocs) //need to get func
			{
				if (node->fd_in)
					close(node->fd_in);
				heredoc_check(node, j);
				j += 2;
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
				// exit_shell(shell()->status);
			}
			if (input_is_dir(node, env) == 1)
				exit_shell(shell()->status);
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
			if (ft_strncmp(node->cmd->file[i], "<", 1) == 0)
				assign_fds(node);
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
			return ;
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
