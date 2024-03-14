/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_ultils.c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:18:32 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 17:43:07 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	command(t_parser *parser)
{
	return (token_list(parser));
}

bool	handle_command_arg_quotes_env_var(t_parser *parser)
{
	if (!grammar_quotes(parser))
		return (false);
	parser->tokens = parser->tokens->next;
	if (!token_list(parser))
		return (false);
	return (true);
}

bool	handle_redirect(t_parser *parser)
{
	if (!grammar_redirection(parser))
		return (false);
	if (!token_list(parser))
		return (false);
	return (true);
}

bool	handle_heredoc(t_parser *parser)
{
	if (!grammar_here_document(parser))
		return (false);
	if (!token_list(parser))
		return (false);
	return (true);
}

bool	token_list(t_parser *parser)
{
	if (!parser->tokens)
		return (true);
	if (parser->tokens->type == TYPE_COMMAND || parser->tokens->type == TYPE_ARG
		|| parser->tokens->type == TYPE_QUOTES
		|| parser->tokens->type == TYPE_ENV_VAR)
		return (handle_command_arg_quotes_env_var(parser));
	else if (parser->tokens->type == TYPE_REDIRECT)
		return (handle_redirect(parser));
	else if (parser->tokens->type == TYPE_HEREDOC)
		return (handle_heredoc(parser));
	return (true);
}
