/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:06:04 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/14 16:59:26 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_msg(void)
{
	perror("ERROR");
	shell()->status = EXIT_FAILURE;
	exit_shell(shell()->status);
}

void	*ft_my_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	original_size;
	size_t	mem_content;

	if (size == 0)
	{
		if (ptr != NULL)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	new_ptr = malloc(size);
	original_size = ft_strlen(ptr) + 1;
	if (original_size < size)
		mem_content = original_size;
	else
		mem_content = size;
	ft_memcpy(new_ptr, ptr, mem_content);
	free(ptr);
	return (new_ptr);
}

char	*read_from_stdin(char **delim, char *buffer, size_t buffer_size)
{
	char	ch;
	char	*delim_line;
	char	*last_line_start;

	handle_signal(SIG_HEREDOC);
	delim_line = ft_strjoin(delim[1], "\n");
	while (read(STDIN_FILENO, &ch, 1) > 0)
	{
		buffer = ft_my_realloc(buffer, buffer_size + 2);
		buffer[buffer_size++] = ch;
		buffer[buffer_size] = '\0';
		last_line_start = buffer + buffer_size - ft_strlen(delim_line);
		if (last_line_start >= buffer && (last_line_start == buffer
				|| *(last_line_start - 1) == '\n')
			&& ft_strncmp(last_line_start, delim_line,
				ft_strlen(delim_line)) == 0)
		{
			buffer_size -= ft_strlen(delim_line);
			buffer[buffer_size] = '\0';
			break ;
		}
	}
	free(delim_line);
	handle_signal(SIG_DEFAULT);
	return (buffer);
}

int	heredoc(t_node *node)
{
	char	*buffer;
	size_t	buffer_size;
	int		here_doc_fd;

	handle_signal(SIG_HEREDOC);
	buffer = NULL;
	buffer_size = 0;
	buffer = read_from_stdin(node->cmd->heredoc, buffer, buffer_size);
	here_doc_fd = open("./in.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd < 0)
		error_msg();
	write(here_doc_fd, buffer, ft_strlen(buffer));
	close(here_doc_fd);
	node->fd_in = open("./in.txt", O_RDONLY);
	if (node->fd_in < 0)
		error_msg();
	unlink("in.txt");
	free(buffer);
	handle_signal(SIG_DEFAULT);
	return (node->fd_in);
}

void	get_file_append(t_node *node)
{
	if (is_dir(node) == 0)
	{
		if (access(node->cmd->file[1], F_OK) != 0)
		{
			status_error(node->cmd->file[1], "No such file or directory",
				STDERR_FILENO);
			shell()->status = EXIT_FAILURE;
		}
		if (access(node->cmd->file[1], X_OK) == 0)
		{
			status_error(node->cmd->file[1], "Permission denied",
				STDERR_FILENO);
			shell()->status = EXIT_FAILURE;
		}
		else
		{
			node->fd_out = open(node->cmd->file[1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
	}
}
