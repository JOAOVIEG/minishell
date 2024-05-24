/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:04:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/18 21:31:03 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_redir(t_node *node)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!node || !node->cmd || node->cmd->heredoc == NULL)
		return (0);
	while (node->cmd->heredoc && node->cmd->heredoc[i])
	{
		if (ft_strncmp(node->cmd->heredoc[i], "<<", 2) == 0)
		{
			j++;
		}
		i++;
	}
	return (j);
}

char	*append_char_to_buffer(char *buffer, size_t *buffer_size, char ch)
{
	buffer = ft_my_realloc(buffer, *buffer_size + 2);
	buffer[*buffer_size] = ch;
	(*buffer_size)++;
	buffer[*buffer_size] = '\0';
	return (buffer);
}

void	heredoc_dad(t_node *node, pid_t heredoc_pid, int k_fd[2], int k)
{
	close(k_fd[1]);
	read(k_fd[0], &k, sizeof(k));
	close(k_fd[0]);
	parent_control(node, heredoc_pid);
	k++;
}

void	heredoc_son(t_node *node, int k_fd[2], int k, int i)
{
	int	num_heredocs;
	int	j;

	num_heredocs = count_redir(node);
	j = 0;
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
		while (node->cmd->file[i])
			handle_file_redir(node, i++);
	}
	child_control(node);
}

void	fork_check(pid_t heredoc_pid)
{
	if (heredoc_pid < 0)
	{
		perror("Error forking");
		shell()->status = EXIT_FAILURE;
		exit_shell(shell()->status);
	}
}
