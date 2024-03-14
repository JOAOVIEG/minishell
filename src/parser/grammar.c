/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:04:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 17:54:00 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
<command line> : <command> '|' <command line>     # A command line can be a command followed by a pipe and another command line,
	or just a command.
				| <command>                        # A command line can also be a standalone command.
				;

<command>      : <token list>                     # A command is a sequence of tokens.
				;

<token list>   : [name]  <token list>             # A token list can start with a name followed by more tokens.
				| [token] <token list>             # Alternatively,
					it can start with a token followed by more tokens.
				| [redir] <token list>             # Or it can start with a redirection followed by more tokens.
				| [quote] <token list>             # Or it can start with a quoted sequence followed by more tokens.
				| [env_var] <token list>           # Or it can start with an environment variable followed by more tokens.
				| '$?' <token list>                # Or it can start with '$?' followed by more tokens.
				| ""                                # Or it can be an empty token list.
				;

<redir>        : <redir in>                       # A redirection can be an input redirection.
				| <redir out>                      # Or it can be an output redirection.
				;

<redir in>     : '<<' [file]                      # Input redirection can be '<<' followed by a file.
				| '<'  [file]                      # Or it can be '<' followed by a file.
				;

<redir out>    : '>>' [file]                      # Output redirection can be '>>' followed by a file.
				| '>'  [file]                      # Or it can be '>' followed by a file.
				;

<quote>        : '\'' [sequence] '\''              # A quoted sequence enclosed in single quotes.
				| '"'  [sequence] '"'               # A quoted sequence enclosed in double quotes.
				;

<sequence>     : [char] <sequence>                # A sequence is a character followed by more characters.
				| ""                               # Or it can be an empty sequence.
				;

<env_var>      : '$' [variable]                   # An environment variable starts with '$' followed by a variable.
				;

<variable>     : [char] <variable>                # A variable is a character followed by more characters.
				| ""                               # Or it can be an empty variable.
				;

 */

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
	command(parser);
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
