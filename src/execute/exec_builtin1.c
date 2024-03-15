/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:57:59 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/14 23:53:04 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_append_to(t_node *node, int i)
{
	if (node->fd_out)
		close(node->fd_out);
	if (access(node->cmd->file[i], X_OK) == 0)
	{
		status_error(node->cmd->file[i], "Permission denied", STDERR_FILENO);
		shell()->status = EXIT_FAILURE;
	}
	else 
	{
		node->fd_out = open(node->cmd->file[i], \
						O_WRONLY | O_CREAT | O_APPEND, 0644);
		shell()->status = EXIT_SUCCESS;
	}
	return (node->fd_out);
}

int	open_file_from(t_node *node, int i)
{
	if (access(node->cmd->file[i], F_OK) == 0)
	{
		close(node->fd_in);
		node->fd_in = open(node->cmd->file[i], O_RDONLY);
		if (node->fd_in < 0)
		{
			status_error(node->cmd->file[i], "Erro at fd_in", STDERR_FILENO);
			shell()->status = EXIT_FAILURE;
		}
	}
	else
	{
		status_error(node->cmd->file[i], "No such file or directory", STDERR_FILENO);
		shell()->status = EXIT_FAILURE;
		return (-1);
	}
	return (node->fd_in);
}

void	handle_file_redir(t_node *node, int i)
{
	struct stat	st;

	if (ft_strncmp(node->cmd->file[i], "<", 1) == 0)
	{
		i++;
		if (stat(node->cmd->file[i], &st) == 0 && S_ISDIR(st.st_mode))
		{
			status_error(node->cmd->file[i], "is directory", STDERR_FILENO);
			shell()->status = EXIT_FAILURE;
			return ;
		}
		if (open_file_from(node, i++) == -1)
			return ;
	}
	else if (ft_strncmp(node->cmd->file[i], ">>", 2) == 0)
	{
		i++;
		if (is_dir_i(node, i) == 0)
			node->fd_out = open_append_to(node, i++);
		else
			return ;
	}
	else if (ft_strncmp(node->cmd->file[i], ">", 1) == 0)
	{
		i++;
		if (is_dir_i(node, i) == 0)
			node->fd_out = open_file_to(node, i++);
		else
			return ;
	}
}
