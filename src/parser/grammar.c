/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:04:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/11 17:38:38 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		printf("Syntax error: unexpected token `|'\n");
		return (false);
	}
	command(parser);
	if (!parser->tokens || parser->tokens->type != TYPE_PIPE)
		return (true);
	parser->tokens = parser->tokens->next;
	if (!parser->tokens)
	{
		printf("Syntax error: expected a command after the pipe\n");
		return (false);
	}
	return (command_line(parser));
}

bool	command(t_parser *parser)
{
	return (token_list(parser));
}

bool	here_document(t_parser *parser)
{
	if (!parser->tokens)
	{
		printf("Syntax error: unexpected end of input after here document\n");
		return (false);
	}
	if (parser->tokens->type == TYPE_HEREDOC)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			printf("Syntax error: expected a file after here document\n");
			return (false);
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}

bool	env_var(t_parser *parser)
{
	char	*p;

	if (!parser->tokens)
	{
		printf("Syntax error: unexpected end of input after environment variable\n");
		return (false);
	}
	if (parser->tokens->type == TYPE_ENV_VAR)
	{
		if (parser->tokens->data[0] != '$'
			|| ft_strlen(parser->tokens->data) < 2)
		{
			printf("Syntax error: malformed environment variable\n");
			return (false);
		}
		p = parser->tokens->data + 1;
		while (*p)
		{
			if (!ft_isalnum(*p) && *p != '_')
			{
				printf("Syntax error: malformed environment variable\n");
				return (false);
			}
			p++;
		}
		parser->tokens = parser->tokens->next;
	}
	return (true);
}

bool	token_list(t_parser *parser)
{
	if (!parser->tokens)
		return (true);
	if (parser->tokens->type == TYPE_COMMAND || parser->tokens->type == TYPE_ARG
		|| parser->tokens->type == TYPE_QUOTES
		|| parser->tokens->type == TYPE_ENV_VAR)
	{
		if (!quotes(parser))
			return (false);
		parser->tokens = parser->tokens->next;
		if (!token_list(parser))
			return (false);
	}
	else if (parser->tokens->type == TYPE_REDIRECT)
	{
		if (!gramar_redirection(parser))
			return false;
		if (!token_list(parser))
			return false;
	}
	else if (parser->tokens->type == TYPE_HEREDOC)
	{
		if (!here_document(parser))
			return false;
		if (!token_list(parser))
			return false;
	}
	return true;
}

bool	gramar_redirection(t_parser *parser)
{
	if (!parser->tokens)
	{
		printf("Syntax error: unexpected end of input after redirection\n");
		return false;
	}
	if (parser->tokens->type == TYPE_REDIRECT)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			printf("Syntax error: expected a file after redirection\n");
			return false;
		}
		parser->tokens = parser->tokens->next;
	}
	return true;
}

bool	quotes(t_parser *parser)
{
	int	len;

	if (!parser->tokens)
		return true;
	len = ft_strlen(parser->tokens->data);
	if (parser->tokens->data[0] == '\'' || parser->tokens->data[0] == '\"')
	{
		if (len < 2 || parser->tokens->data[len - 1] != parser->tokens->data[0])
		{
			printf("Syntax error: expected a closing quote\n");
			return false;
		}
	}
	else if (parser->tokens->data[len - 1] == '\'' || parser->tokens->data[len
		- 1] == '\"')
	{
		if (len < 2 || parser->tokens->data[0] != parser->tokens->data[len - 1])
		{
			printf("Syntax error: expected a closing quote\n");
			return false;
		}
	}
	return true;
}

bool	grammar_check(t_parser *parser)
{
	t_lst_tokens	*head;

	if (!parser->tokens)
		return true;
	head = parser->tokens;
	if (!command_line(parser))
	{
		printf("Syntax error\n");
		return false;
	}
	if (parser->tokens)
	{
		return false;
	}
	parser->tokens = head;
	return true;
}
