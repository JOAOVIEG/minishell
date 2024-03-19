/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:14:38 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/19 13:33:07 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_is_dir(t_node *node, char **env)
{
	struct stat	st;

	if (stat(node->cmd->arg[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		free_c_env(env);
		status_error(node->cmd->arg[0], "is a directory", STDERR_FILENO);
		shell()->status = 126;
		return (1);
	}
	return (0);
}

int	is_dir_i(t_node *node, int i)
{
	struct stat	st;

	if (stat(node->cmd->file[i], &st) == 0 && S_ISDIR(st.st_mode))
	{
		status_error(node->cmd->file[1], " is a directory", STDERR_FILENO);
		shell()->status = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

int	is_dir(t_node *node)
{
	struct stat	st;

	if (stat(node->cmd->file[1], &st) == 0 && S_ISDIR(st.st_mode))
	{
		status_error(node->cmd->file[1], " is a directory", STDERR_FILENO);
		shell()->status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	no_cmd_file_redir(t_node *node)
{
	pid_t	heredoc_pid;
	int		i;
	int		k;
	int		k_fd[2];

	k = 1;
	i = 0;
	if (node->cmd->arg[0] == NULL && node->cmd->heredoc)
	{
		if (pipe(k_fd) == -1)
		{
			perror("pipe");
			exit_shell(EXIT_FAILURE);
		}
		heredoc_pid = fork();
		fork_check(heredoc_pid);
		if (heredoc_pid == 0)
			heredoc_son(node, k_fd, k, i);
		else
			heredoc_dad(node, heredoc_pid, k_fd, k);
	}
	else if (node->cmd->arg[0] == NULL && node->cmd->file \
							&& *node->cmd->file)
		create_file(node);
}

void	assign_fds(t_node *node)
{
	if (!node->fd_in)
		node->fd_in = dup(STDIN_FILENO);
	if (!node->fd_out)
		node->fd_out = dup(STDOUT_FILENO);
}
