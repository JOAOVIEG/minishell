/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_here_document.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:52:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/09 09:54:52 by wiferrei         ###   ########.fr       */
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
	{
		ft_putstr_fd("bash: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd(token->data, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	shell()->status = 2;
}

bool	grammar_here_document(t_parser *parser)
{
	if (!parser->tokens)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n",
			STDERR_FILENO);
		shell()->status = 2;
		return (false);
	}
	if (parser->tokens->type == TYPE_HEREDOC)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			if (parser->tokens)
				hd_error(parser->tokens);
			else
			{
				ft_putstr_fd("bash: syntax error: unexpected end of file\n",
					STDERR_FILENO);
				shell()->status = 2;
			}
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
