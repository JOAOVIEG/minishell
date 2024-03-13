/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:41:30 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/13 16:26:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	grammar_quotes(t_parser *parser)
{
	int	len;

	if (!parser->tokens)
		return (true);
	len = ft_strlen(parser->tokens->data);
	if (parser->tokens->data[0] == '\'' || parser->tokens->data[0] == '\"')
	{
		if (len < 2 || parser->tokens->data[len - 1] != parser->tokens->data[0])
		{
			status_error("",
				"Syntax error: expected a closing quote",
				STDERR_FILENO);
			shell()->status = 2;
			return (false);
		}
	}
	else if (parser->tokens->data[len - 1] == '\''
		|| parser->tokens->data[len - 1] == '\"')
	{
		if (len < 2 || parser->tokens->data[0] != parser->tokens->data[len - 1])
		{
			status_error("",
				"Syntax error: expected a closing quote",
				STDERR_FILENO);
			shell()->status = 2;
			return (false);
		}
	}
	return (true);
}
