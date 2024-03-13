/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_here_document.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/13 16:25:31 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	grammar_here_document(t_parser *parser)
{
	if (!parser->tokens)
	{
		status_error("",
			"Syntax error: unexpected end of input after here document",
			STDERR_FILENO);
		shell()->status = 2;
		return (false);
	}
	if (parser->tokens->type == TYPE_HEREDOC)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			status_error("",
				"Syntax error: expected a file after here document",
				STDERR_FILENO);
			shell()->status = 2;
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
