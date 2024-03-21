/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_here_document.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/21 20:40:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hd_error(t_lst_tokens *token)
{
	if (token->type == TYPE_PIPE)
		status_error("bash", "syntax error near unexpected token `|'",
			STDERR_FILENO);
	else if (token->type == TYPE_REDIRECT)
	{
		if (ft_strcmp(token->data, "<") == 0)
			status_error("bash",
				"syntax error near unexpected token `new line'", STDERR_FILENO);
		else
			printf("bash: syntax error near unexpected token `%s'\n",
				token->data);
	}
	else
		printf("bash: syntax error near unexpected token `%c'\n",
			token->data[0]);
	shell()->status = 2;
}

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
			hd_error(parser->tokens);
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
