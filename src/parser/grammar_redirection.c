/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:51:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/11 18:52:10 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	grammar_redirection(t_parser *parser)
{
	if (!parser->tokens)
	{
		printf("Syntax error: unexpected end of input after redirection\n");
		return (false);
	}
	if (parser->tokens->type == TYPE_REDIRECT)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			printf("Syntax error: expected a file after redirection\n");
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
