/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:04:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/17 21:01:06 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	command_line(t_parser *parser)
{
	if (!parser->tokens)
		return (true);
	if (parser->tokens->type == TYPE_PIPE)
	{
		status_error("|", "Syntax error: unexpected token", STDERR_FILENO);
		shell()->status = 2;
		return (false);
	}
	if (!command(parser))
		return (false);
	if (!parser->tokens || parser->tokens->type != TYPE_PIPE)
		return (true);
	parser->tokens = parser->tokens->next;
	if (!parser->tokens)
	{
		status_error("|", "Syntax error: expected a command after the pipe",
			STDERR_FILENO);
		shell()->status = 2;
		return (false);
	}
	return (command_line(parser));
}

bool	grammar_check(t_parser *parser)
{
	t_lst_tokens	*head;

	if (!parser->tokens)
		return (true);
	head = parser->tokens;
	if (!command_line(parser))
		return (false);
	if (parser->tokens)
		return (false);
	parser->tokens = head;
	return (true);
}
