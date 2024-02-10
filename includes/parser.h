/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:08:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/10 18:16:33 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "minishell.h"
# include <stdbool.h>

typedef enum e_token_type
{
	TYPE_PIPE,
	TYPE_COMMAND,
	TYPE_ARG,
	TYPE_REDIRECT,
	TYPE_HEREDOC,
	TYPE_QUOTES,
	TYPE_ENV_VAR
}						t_token_type;

typedef struct s_lst_tokens
{
	char				*data;
	t_token_type		type;
	struct s_lst_tokens	*next;
}						t_lst_tokens;

typedef struct s_buffer
{
	t_lst_tokens		*lst_tok;
	t_lst_tokens		*next;
}						t_buffer;

typedef struct s_parser
{
	t_lst_tokens		*tokens;
	int					pipe_count;
	t_buffer			*buffer;

}						t_parser;

t_parser				*init_parser(void);

void					parse_to_list(t_lexer *lexer, t_parser *parser);
void					add_to_end(t_lst_tokens **head, char *data);

void					define_type(t_lst_tokens *current, t_lst_tokens *prev);
void					get_token_type(t_lst_tokens *tokens);

void					print_list(t_lst_tokens *head);

// grammar
void					command_line(t_parser *parser);
void					command(t_parser *parser);
void					token_list(t_parser *parser);
void					redir_out(t_parser *parser);
void					redir_in(t_parser *parser);
void					redirection(t_parser *parser);
void					quotes(t_parser *parser);
void					sequence(t_parser *parser);
bool					grammar_check(t_parser *parser);

// AST
void					split_list(t_parser *parser);
void					tree_simple_command(t_parser *parser);

// free_parser
void					reset_parser(t_parser *parser);
void					free_lst_tokens(t_lst_tokens *tokens);

#endif
