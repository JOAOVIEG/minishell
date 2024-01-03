/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:00:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/03 15:58:16 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0 || ft_strncmp(command, "unset",
			6) == 0)
		return (true);
	return (false);
}

int	error_message_cmd(char *command, char *detail, char *error_msg,
		int error_nbr)
{
	char	*message;
	bool	details_quotes;

	details_quotes = add_detail_quotes(command);
	message = ft_strdup("minishell: ");
	if (command)
	{
		message = join_strs(message, command);
		message = join_strs(message, ": ");
	}
	if (detail)
	{
		if (details_quotes)
			message = join_strs(message, "'");
		message = join_strs(message, detail);
		if (details_quotes)
			message = join_strs(message, "'");
		message = join_strs(message, ": ");
	}
	message = join_strs(message, error_msg);
	ft_putendl_fd(message, 2);
	free_ptr(message);
	return (error_nbr);
}

void	exit_shell(t_data *data, int exno)
{
	if (data)
	{
		if (data->cmd && data->cmd->io_fds)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exno);
}

bool	usage_message(bool return_val)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_val);
}
