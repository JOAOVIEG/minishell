/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:00:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 14:20:36 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_token_type
{
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SINGLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE_SEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	CHAR_GENERAL,
	TOKEN = -1,

}					t_token_type;

enum
{
	STATE_IN_DQUOTE,
	STATE_IN_SQUOTE,
	STATE_IN_SCAEPE_SEQUENCE,
	STATE_IN_GENERAL,

};

typedef struct s_lx_state
{
	char			*input;
	size_t			current_position;
}					t_lx_state;

typedef struct s_tk_buffer
{
	int				i;
	int				j;
	int				state;
	char			current;
	int				char_type;
}					t_tk_buffer;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				precedence;
	struct s_token	*next;

}					t_token;

typedef struct s_lexer
{
	int				ntoks;
	t_token			*tokens;
	t_lx_state		state;
}					t_lexer;

void				tokenize_input(t_lexer *lexer);
t_lexer				*init_lexer(void);
void				init_lexer_state(t_lx_state *lexer_state, char *input);
void				add_current_position(t_lx_state *lexer_state);
char				current_char(const t_lx_state *lexer_state);
void				print_input(const t_lx_state *lexer_state);
void				token_init(t_token *token);
int					get_char_type(char c);
//_token_type		get_token_type(t_token *token);

// tokens functions
t_token				*new_token(void);
t_token				*build_token(t_lexer *lexer, t_token *token);
void				handle_single_quote_char(t_token *token,
						t_tk_buffer *buffer);
void				handle_double_quote_char(t_token *token,
						t_tk_buffer *buffer);
void				handle_escape_sequence_char(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);
void				handle_general_char(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);
void				handle_general_char(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);
void				handle_whitespace_char(t_token **token,
						t_tk_buffer *buffer);
void				handle_special_char(t_token **token, t_tk_buffer *buffer);
t_token				*handle_state_general(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);
t_token				*handle_state_in_dquote(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);
t_token				*handle_state_in_squote(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);
t_token				*handle_null(t_token *token, t_lexer *lexer,
						t_tk_buffer *buffer);

# ifndef MAX_TOKEN_SIZE
#  define MAX_TOKEN_SIZE 1024
# endif

#endif
