/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:28:37 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/08 14:27:39 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(int fd_i, int fd_o)
{
	if (fd_i != STDIN_FILENO)
		close(fd_i);
	if (fd_o != STDOUT_FILENO)
		close(fd_o);
}

int	redirections(int fd_i, int fd_o)
{
	if (redirect_in(fd_i) == -1 || redirect_out(fd_o) == -1)
		return (-1);
	return (0);
}

int	redirect_in(int fd_i)
{
	int	red_i;

	if (fd_i == STDIN_FILENO)
		return (STDIN_FILENO);
	else
	{
		red_i = dup2(fd_i, STDIN_FILENO);
		if (red_i < 0)
			return (-1);
		close(fd_i);
	}
	return (red_i);
}

int	redirect_out(int fd_o)
{
	int	red_o;

	if (fd_o == STDOUT_FILENO)
		return (STDOUT_FILENO);
	else
	{
		red_o = dup2(fd_o, STDOUT_FILENO);
		if (red_o < 0)
			return (-1);
		close(fd_o);
	}
	return (red_o);
}

void	get_file(t_node *node)
{
	if (is_dir(node) == 0)
	node->fd_out = open(node->cmd->file[1], \
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
