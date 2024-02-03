/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:32:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/03 19:59:53 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_built_in(char *data)
{
	if (ft_strcmp(data, "cd") == 0 || ft_strcmp(data, "pwd") == 0
		|| ft_strcmp(data, "echo") == 0 || ft_strcmp(data, "exit") == 0
		|| ft_strcmp(data, "env") == 0 || ft_strcmp(data, "export") == 0
		|| ft_strcmp(data, "unset") == 0)
		return (1);
	return (0);
}

int	is_a_command(char *data)
{
	if (is_a_built_in(data))
		return (1);
	/* In a shell like bash,
		a token is considered a command if it is the first word of a command line or after a pipe (|),
		a semicolon (;), or a logical operator (&& or ||). */
	// need to implement this :)
	return (0);
}

void	get_token_type(t_lst_tokens *tokens)
{
	t_lst_tokens	*current;

	current = tokens;
	while (current != NULL)
	{
		if (ft_strncmp(current->data, "|", 2) == 0)
			current->type = TYPE_PIPE;
		else if (ft_strncmp(current->data, ">", 2) == 0
			|| ft_strncmp(current->data, "<", 2) == 0)
			current->type = TYPE_REDIRECT;
		else if (ft_strncmp(current->data, ">>", 3) == 0)
			current->type = TYPE_REDIRECT;
		else if (ft_strncmp(current->data, "<<", 3) == 0)
			current->type = TYPE_HEREDOC;
		else if (ft_strncmp(current->data, "'", 2) == 0)
			current->type = TYPE_QUOTES;
		else if (ft_strncmp(current->data, "\"", 2) == 0)
			current->type = TYPE_QUOTES;
		else if (ft_strncmp(current->data, "$", 2) == 0)
			current->type = TYPE_ENV_VAR;
		else if (is_a_command(current->data))
			current->type = TYPE_COMMAND;
		else
			current->type = TYPE_ARG;
		current = current->next;
	}
}
