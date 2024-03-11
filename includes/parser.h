/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:08:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/11 19:15:57 by wiferrei         ###   ########.fr       */
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
}								t_token_type;

typedef enum e_quote_type
{
	NO_QUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	SINGLE_IN_DOUBLE_QUOTED,
	DOUBLE_IN_SINGLE_QUOTED

}								t_quote_type;

typedef struct s_shell			t_shell;
typedef struct s_node			t_node;
typedef struct s_cmd			t_cmd;
typedef struct s_history_entry	t_history_entry;

typedef struct s_lst_tokens
{
	char						*data;
	t_token_type				type;
	struct s_lst_tokens			*next;
}								t_lst_tokens;

typedef struct s_token_queue
{
	t_lst_tokens				*head;
	t_lst_tokens				*tail;
}								t_token_queue;

typedef struct s_buffer
{
	t_token_queue				cmds;
	t_token_queue				heredocs;
	t_token_queue				redir_files;
}								t_buffer;

typedef struct s_env_var_replacement
{
	t_lst_tokens				**current;
	char						*start;
	char						*end;
	char						*value;
	char						*substring;
}								t_env_var_replacement;

typedef struct s_parser
{
	t_lst_tokens				*tokens;
	int							pipe_count;
	int							redir_count;
	int							heredoc_count;

}								t_parser;

t_parser						*init_parser(void);
void							parse_to_list(t_lexer *lexer, t_parser *parser);
void							add_to_end(t_lst_tokens **head, char *data);
void							define_type(t_lst_tokens *current,
									t_lst_tokens *prev);
void							get_token_type(t_lst_tokens *tokens);
void							print_list(t_lst_tokens *head);
bool							grammar_check(t_parser *parser);
bool							command_line(t_parser *parser);
bool							command(t_parser *parser);
bool							grammar_here_document(t_parser *parser);
bool							grammar_env_var(t_parser *parser);
bool							token_list(t_parser *parser);
bool							grammar_redirection(t_parser *parser);
bool							grammar_quotes(t_parser *parser);

// AST
void							lst_tokenadd_back(t_lst_tokens **lst,
									t_lst_tokens **tail, t_lst_tokens *new);
int								lst_token_size(t_lst_tokens *tokens);
void							parser(t_shell *shell);
void							build_tree(t_shell *shell);
void							build_tree_simple_command(t_shell *shell);
t_node							*new_tree_node(t_lst_tokens *tokens);
void							build_pipe_tree(t_shell *shell);
void							print_tree(t_node *node, int space, char *type);
t_lst_tokens					*new_node(char *data);

// free_parser
void							reset_parser(t_parser *parser);
void							free_lst_tokens(t_lst_tokens *tokens);
void							free_parser(t_parser *parser);
void							free_history(t_history_entry *history);
void							delete_node(t_lst_tokens *node);

// need replace these functions
t_node							*create_node(t_token_type type, t_cmd *cmd,
									t_node *left, t_node *right);
t_node							*init_pipe_node(void);
t_node							*create_pipe_node(t_node *left, t_node *right);
t_node							*find_parent(t_node *root, t_node *node);
void							update_tree_root(t_node **tree_root,
									t_node **rightmost_node, t_node *pipe_node);
t_lst_tokens					*get_cmd_tokens(t_lst_tokens **current);
t_node							*create_new_node(t_lst_tokens **cmd_tokens);
t_node							*create_node_and_update_tree(t_node **tree_root,
									t_node **rightmost_node,
									t_lst_tokens **cmd_tokens);
t_cmd							*create_cmd(t_lst_tokens *tokens);
void							build_redir_tree(t_shell *shell);
void							build_redir_pipe_tree(t_shell *shell);
void							add_token_back(t_lst_tokens **current,
									t_lst_tokens **cmd_tokens,
									t_lst_tokens **tail);
void							print_type(int type);
void							build_heredoc_tree(t_shell *shell);
void							build_heredoc_pipe_tree(t_shell *shell);
void							build_heredoc_redir_tree(t_shell *shell);
void							print_env_list(t_env *env);
void							init_token_queue(t_token_queue *queue);
void							init_buffer(t_buffer *buffer);
void							clean_token_queue(t_token_queue *queue);
void							clean_buffer(t_buffer *buffer);
t_lst_tokens					*get_redir_list(t_lst_tokens **current,
									t_lst_tokens **cmd_tokens,
									t_lst_tokens **tail);
t_lst_tokens					*get_cmd_list(t_lst_tokens **current,
									t_lst_tokens **cmd_tokens,
									t_lst_tokens **tail);
char							**get_redir_files(t_lst_tokens *tokens);
t_node							*new_redir_tree_node(t_buffer buffer);
void							build_token_queue(t_lst_tokens **current,
									t_buffer *buffer);
t_node							*create_node_and_update_redir_pipe_tree(t_node **tree_root,
									t_node **rightmost_node, t_buffer buffer);
void							build_heredoc_redir_queue(t_lst_tokens **current,
									t_token_queue *cmds,
									t_token_queue *heredocs,
									t_token_queue *redir_files);
void							build_heredoc_redir_pipe_tree(t_shell *shell);

void							count_pipe_redir(t_parser *parser);
void							make_expansion(t_shell *shell);
void							replace_env_var_in_token(t_lst_tokens **current,
									t_env *env);
void							replace_with_env_var(t_lst_tokens **current,
									t_env *env);
char							*find_env_value(t_env *env, char *trimmed);
void							make_the_replacement(t_env_var_replacement *replacement,
									char *trimmed);
void							env_var_not_found(t_env_var_replacement *replacement,
									char *trimmed);
void							init_env_var_replacement(t_lst_tokens **current,
									t_env_var_replacement *replacement);
char							*create_env_data(t_env_var_replacement *replacement);
char							*find_end_of_env_var(const char *str);

void							print_quoted(t_shell shell);
t_quote_type					env_var_quotes(t_lst_tokens *current);
void							remove_quotes(t_parser *parser);
void							print_env_list(t_env *env);
void							add_to_history(t_shell *shell, char *command);
void							handle_sigint(int sig);

void							ignore_signals(void);
void							handle_eof(void);

#endif