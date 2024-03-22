/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:51:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/22 16:11:28 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirection_error(t_lst_tokens *token)
{
	if (!token)
	{
		status_error("bash", "syntax error near unexpected token `newline'",
			STDERR_FILENO);
		shell()->status = 2;
		return ;
	}
	else if (token->type == TYPE_PIPE)
		status_error("bash", "syntax error near unexpected token `|'",
			STDERR_FILENO);
	else if (token->type == TYPE_REDIRECT)
	{
		if (ft_strcmp(token->data, ">") == 0)
			status_error("bash", "syntax error near unexpected token `>'",
				STDERR_FILENO);
		else
			status_error("bash", "syntax error near unexpected token `<",
				STDERR_FILENO);
	}
	else
		printf("bash: syntax error near unexpected token `%c'\n",
			token->data[0]);
	shell()->status = 2;
}

bool	grammar_redirection(t_parser *parser)
{
	if (!parser->tokens)
	{
		redirection_error(parser->tokens);
		return (false);
	}
	if (parser->tokens->type == TYPE_REDIRECT)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			redirection_error(parser->tokens);
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
