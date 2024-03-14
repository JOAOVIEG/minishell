/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:14:38 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/14 16:56:55 by joaocard         ###   ########.fr       */
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

	if (node->cmd->arg[0] == NULL && node->cmd->heredoc && !node->fd_in)
	{
		heredoc_pid = fork();
		if (heredoc_pid < 0)
		{
			perror("Error forking");
			shell()->status = EXIT_FAILURE;
			exit_shell(shell()->status);
		}
		else if (heredoc_pid == 0)
		{
			if (!node->fd_in)
				heredoc_check(node);
			close(node->fd_in);
			if (node->fd_out)
				close(node->fd_out);
			if (node->cmd->file && *node->cmd->file)
			{
				i = 0;
				while(node->cmd->file[i])
					handle_file_redir(node, i++);
			}
			child_control(node);
		}
		else
			parent_control(node, heredoc_pid);
	}
	else if (node->cmd->arg[0] == NULL && node->cmd->file \
						 && *node->cmd->file && !node->fd_in)
	{
		i = 0;
		while(node->cmd->file[i])
		{
			assign_fds(node);
			handle_file_redir(node, i++);
		}
	}
}

void	assign_fds(t_node *node)
{
	if (!node->fd_in)
	node->fd_in = dup(STDIN_FILENO);
	if (!node->fd_out)
	node->fd_out = dup(STDOUT_FILENO);
}
