/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:51:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 17:37:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	grammar_redirection(t_parser *parser)
{
	if (!parser->tokens)
	{
		status_error("",
			"Syntax error: unexpected end of input after redirection",
			STDERR_FILENO);
		shell()->status = 2;
		return (false);
	}
	if (parser->tokens->type == TYPE_REDIRECT)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			status_error("",
				"Syntax error: expected a file after redirection",
				STDERR_FILENO);
			shell()->status = 2;
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
