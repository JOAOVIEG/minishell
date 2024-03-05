/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:08:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/05 12:00:53 by wiferrei         ###   ########.fr       */
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
	TYPE_REDIRECT_IN,
	TYPE_REDIRECT_OUT,
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

typedef struct s_token_queue
{
	t_lst_tokens		*head;
	t_lst_tokens		*tail;
}						t_token_queue;

typedef struct s_buffer
{
	t_lst_tokens		*lst_tok;
	t_lst_tokens		*next;
}						t_buffer;

typedef struct s_parser
{
	t_lst_tokens		*tokens;
	int					pipe_count;
	int					redir_count;
	int					heredoc_count;
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
int						lst_token_size(t_lst_tokens *tokens);
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

// need replace these functions

t_node					*create_node(t_token_type type, t_cmd *cmd,
							t_node *left, t_node *right);
t_node					*init_pipe_node(void);
t_node					*init_redir_node(void);
t_node					*create_pipe_node(t_node *left, t_node *right);

t_node					*find_parent(t_node *root, t_node *node);
void					update_tree_root(t_node **tree_root,
							t_node **rightmost_node, t_node *pipe_node);
t_lst_tokens			*get_cmd_tokens(t_lst_tokens **current);
t_node					*create_new_node(t_lst_tokens **cmd_tokens);
t_node					*create_node_and_update_tree(t_node **tree_root,
							t_node **rightmost_node, t_lst_tokens **cmd_tokens);

t_cmd					*create_cmd(t_lst_tokens *tokens);
void					build_pipe_tree(t_shell *shell);
void					build_tree_simple_command(t_shell *shell);
void					build_tree(t_shell *shell);
void					build_redir_tree(t_shell *shell);
t_node					*build_redir_root_node(t_lst_tokens **current,
							t_node *tree_root);
void					define_direction(t_node *node);
void					build_redir_pipe_tree(t_shell *shell);
t_lst_tokens			*build_redir_child_node(t_lst_tokens **current,
							t_lst_tokens **cmd_tokens, t_lst_tokens **tail);
t_node					*find_rightmost_tree_node(t_node *root);
void					add_token_back(t_lst_tokens **current,
							t_lst_tokens **cmd_tokens, t_lst_tokens **tail);
void					print_type(int type);
void					build_heredoc_tree(t_shell *shell);

#endif
