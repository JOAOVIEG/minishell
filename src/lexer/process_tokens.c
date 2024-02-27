/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:24:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/27 16:33:45 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == CHAR_WHITESPACE || c == CHAR_TAB || c == CHAR_NEWLINE)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == CHAR_SINGLE_QUOTE || c == CHAR_DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	skip_whitespace(char *input, int i)
{
	while (is_whitespace(input[i]))
		i++;
	return (i);
}

int	process_quoted_token(char *input, int i, char quote_type)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == CHAR_ESCAPE_SEQUENCE && quote_type == CHAR_DOUBLE_QUOTE)
			i += 2;
		else if (input[i] == quote_type)
		{
			i++;
			break ;
		}
		else
			i++;
	}
	return (i);
}

int	process_unquoted_token(char *input, int i)
{
	while (!is_whitespace(input[i]) && !is_quote(input[i]) && input[i] != '\0'
		&& input[i] != '|')
		i++;
	return (i);
}

int	process_pipe_token(char *input, int i)
{
	if (input[i] == CHAR_PIPE)
		i++;
	return (i);
}

int	process_redirection_token(char *input, int i)
{
	if (input[i] == CHAR_GREATER || input[i] == CHAR_LESSER)
		i++;
	return (i);
}

