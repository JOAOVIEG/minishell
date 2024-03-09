/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:14:38 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/08 14:24:07 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input_is_dir(t_node *node)
{
	struct stat	st;

	if (stat(node->cmd->arg[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		printf("%s: is a directory\n", node->cmd->arg[0]);
		return (1);
	}
	return (0);
}

int	is_dir_i(t_node *node, int i)
{
	struct stat	st;

	if (stat(node->cmd->file[i], &st) == 0 && S_ISDIR(st.st_mode))
	{
		printf("%s: is a directory\n", node->cmd->file[1]);
		return (1);
	}
	return (0);
}

int	is_dir(t_node *node)
{
	struct stat	st;

	if (stat(node->cmd->file[1], &st) == 0 && S_ISDIR(st.st_mode))
	{
		printf("%s: is a directory\n", node->cmd->file[1]);
		return (1);
	}
	return (0);
}

void	no_cmd_file_redir(t_node *node)
{
	if (node->cmd->arg[0] == NULL && node->cmd->heredoc && !node->fd_in)
		node->fd_in = heredoc(node);
	else if (node->cmd->arg[0] == NULL && (node->cmd->file \
							&& ft_strcmp(node->cmd->file[0], "<") == 0) \
			&& !node->fd_in)
	{
		if (access(node->cmd->file[1], F_OK) == 0)
		{
			node->fd_in = open(node->cmd->file[1], O_RDONLY);
			return ;
		}
		else
			printf("minishell: %s: No such file or directory\n", \
												node->cmd->file[1]);
	}
	else if (node->cmd->arg[0] == NULL && (node->cmd->file \
						&& ft_strcmp(node->cmd->file[0], ">") == 0))
		get_file(node);
	else if (node->cmd->arg[0] == NULL && \
		(node->cmd->file && ft_strncmp(node->cmd->file[0], ">>", 2) == 0))
		get_file_append(node);
}

void	assign_fds(t_node *node)
{
	if (!node->fd_in)
		node->fd_in = dup(STDIN_FILENO);
	if (!node->fd_out)
		node->fd_out = dup(STDOUT_FILENO);
}
