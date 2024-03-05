/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:04:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/05 11:38:43 by wiferrei         ###   ########.fr       */
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

void	command_line(t_parser *parser)
{
	if (!parser->tokens)
		return ;
	if (parser->tokens->type == TYPE_PIPE)
	{
		printf("Syntax error: unexpected token `|'\n");
		return ;
	}
	command(parser);
	if (!parser->tokens || parser->tokens->type != TYPE_PIPE)
		return ;
	parser->tokens = parser->tokens->next;
	if (!parser->tokens)
	{
		printf("Syntax error: expected a command after the pipe\n");
		return ;
	}
	command_line(parser);
}

void	command(t_parser *parser)
{
	token_list(parser);
}
void	here_document(t_parser *parser)
{
	if (!parser->tokens)
	{
		printf("Syntax error: unexpected end of input after here document\n");
		return ;
	}
	if (parser->tokens->type == TYPE_HEREDOC)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			printf("Syntax error: expected a file after here document\n");
			return ;
		}
		parser->tokens = parser->tokens->next;
	}
}

void	token_list(t_parser *parser)
{
	if (!parser->tokens)
		return ;
	if (parser->tokens->type == TYPE_COMMAND || parser->tokens->type == TYPE_ARG
		|| parser->tokens->type == TYPE_QUOTES
		|| parser->tokens->type == TYPE_ENV_VAR)
	{
		quotes(parser);
		parser->tokens = parser->tokens->next;
		token_list(parser);
	}
	else if (parser->tokens->type == TYPE_REDIRECT)
	{
		redirection(parser);
		token_list(parser);
	}
	else if (parser->tokens->type == TYPE_HEREDOC)
	{
		here_document(parser);
		token_list(parser);
	}
	else
		return ;
}

void	redirection(t_parser *parser)
{
	if (!parser->tokens)
	{
		printf("Syntax error: unexpected end of input after redirection\n");
		return ;
	}
	if (parser->tokens->type == TYPE_REDIRECT)
	{
		parser->tokens = parser->tokens->next;
		if (!parser->tokens || parser->tokens->type != TYPE_ARG)
		{
			printf("Syntax error: expected a file after redirection\n");
			return ;
		}
		parser->tokens = parser->tokens->next;
	}
}

void	quotes(t_parser *parser)
{
	int	len;

	len = ft_strlen(parser->tokens->data);
	if (parser->tokens->data[0] == '\'' || parser->tokens->data[0] == '\"')
	{
		if (parser->tokens->data[len - 1] != parser->tokens->data[0])
		{
			printf("Syntax error: expected a closing quote\n");
			return ;
		}
	}
	else if (parser->tokens->data[len - 1] == '\'' || parser->tokens->data[len
		- 1] == '\"')
	{
		if (parser->tokens->data[0] != parser->tokens->data[len - 1])
		{
			printf("Syntax error: expected a closing quote\n");
			return ;
		}
	}
}

bool	grammar_check(t_parser *parser)
{
	t_lst_tokens	*head;

	head = parser->tokens;
	command_line(parser);
	if (parser->tokens)
	{
		printf("Syntax error\n");
		return (false);
	}
	parser->tokens = head;
	while (parser->tokens->next)
		parser->tokens = parser->tokens->next;
	if (parser->tokens->type == TYPE_REDIRECT
		|| parser->tokens->type == TYPE_HEREDOC)
	{
		printf("Syntax error\n");
		return (false);
	}
	parser->tokens = head;
	return (true);
}

// For now I'm ignoring the env_var and the $ variable,