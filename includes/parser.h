/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:08:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/14 17:06:06 by wiferrei         ###   ########.fr       */
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

typedef struct s_shell	t_shell;
typedef struct s_node	t_node;
typedef struct s_cmd	t_cmd;

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
void					lst_tokenadd_back(t_lst_tokens **lst,
							t_lst_tokens **tail, t_lst_tokens *new);
void					parser(t_shell *shell);
void					build_tree(t_shell *shell);
void					build_tree_simple_command(t_shell *shell);
t_node					*new_tree_node(t_lst_tokens *tokens);
t_cmd					*create_cmd_from_string(char *str);
void					build_pipe_tree(t_shell *shell);
void					print_tree(t_node *node, int space, char *type);

// free_parser
void					reset_parser(t_parser *parser);
void					free_lst_tokens(t_lst_tokens *tokens);
void					free_parser(t_parser *parser);

#endif
