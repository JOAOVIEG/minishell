/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:04:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/05 19:26:18 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
<job>          : <command> '|' <job>     # Job can be a command followed by a pipe and another job,
	or just a command.

				| <command>               # Job can also be a standalone command.

				;

<command>      : <token list>            # A command is a sequence of tokens.

				;

<token list>   : [name]  <token list>     # A token list can start with a name followed by more tokens.

				| [token] <token list>     # Alternatively,
					it can start with a token followed by more tokens.

				| [redir] <token list>     # Or it can start with a redirection followed by more tokens.

				| [quote] <token list>     # Or it can start with a quoted sequence followed by more tokens.

				| [env_var] <token list>   # Or it can start with an environment variable followed by more tokens.

				| '$?' <token list>        # Or it can start with '$?' followed by more tokens.

				| (null)                   # Or it can be an empty token list.

				;

<redir>        : <redir in>               # A redirection can be an input redirection.

				| <redir out>              # Or it can be an output redirection.

				;

<redir in>     : '<<' [file]              # Input redirection can be '<<' followed by a file.

				| '<'  [file]              # Or it can be '<' followed by a file.

				;

<redir out>    : '>>' [file]              # Output redirection can be '>>' followed by a file.

				| '>'  [file]              # Or it can be '>' followed by a file.

				;

<quote>        : '\'' [sequence] '\''      # A quoted sequence enclosed in single quotes.

				| '"'  [sequence] '"'       # A quoted sequence enclosed in double quotes.

				;

<sequence>     : [char] <sequence>        # A sequence is a character followed by more characters.

				| (null)                   # Or it can be an empty sequence.

				;

<env_var>      : '$' [variable]           # An environment variable starts with '$' followed by a variable.

				;

<variable>     : [char] <variable>        # A variable is a character followed by more characters.

				| (null)                   # Or it can be an empty variable.

				;
 */

/* The job function corresponds to the <job> rule in your grammar.
It first processes a command, then if the next token is a pipe,
	it processes the next job. */
void job(t_parser *parser) {
    // Process a command
    command(parser);

    // If there are no more tokens left, return
    if (!parser->tokens) {
        return;
    }

    // If the next token is a pipe
    if (parser->tokens->type == TYPE_PIPE) {
        // Consume the pipe token, i.e., move the parser's attention to the next token
        parser->tokens = parser->tokens->next;

        // If there are no more tokens left after the pipe, it's a syntax error
        if (!parser->tokens) {
            printf("Syntax error: expected a command after the pipe\n");
            return;
        }

        // Process the next job
        job(parser);
    }
}

/* The command function corresponds to the <command> rule in the  grammar.
It processes a list of tokens,
	which can include a command name and possibly some arguments, redirections,
	etc. */
void	command(t_parser *parser)
{
	token_list(parser);
}

/* The token_list function corresponds to the <token list> rule in your grammar.
It processes a sequence of tokens, consuming tokens as it goes. */
void	token_list(t_parser *parser)
{
	if (!parser->tokens)
	{
		return ;
	}
	/* Check if the token list starts with a name, token, redir, quote,
		env_var or $ */
	if (parser->tokens && (parser->tokens->type == TYPE_COMMAND
			|| parser->tokens->type == TYPE_ARG
			|| parser->tokens->type == TYPE_REDIRECT
			|| parser->tokens->type == TYPE_QUOTES
			|| parser->tokens->type == TYPE_ENV_VAR))
	{
		/* Consume the token,
			means move the parser's attention to the next token */
		parser->tokens = parser->tokens->next;
		/* Process the rest of the token list */
		token_list(parser);
	}
}



void	grammar_check(t_parser *parser)
{

	t_lst_tokens	*head;

	head = parser->tokens;
	/* Check if all the tokens have been consumed, if not,
		means that the input is invalid */
	job(parser);
	if (parser->tokens)
		printf("Syntax error\n");
	// Maybe I need change the function to return a boolean

	parser->tokens = head;
}
