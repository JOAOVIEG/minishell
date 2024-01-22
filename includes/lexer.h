/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:00:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/22 20:17:05 by wiferrei         ###   ########.fr       */
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

// tokens functions
t_token				*new_token(void);
t_token				*build_token(t_lexer *lexer, t_token *token);
void	handle_state_general(t_token *token, t_lexer *lexer, int state,	int char_type);

# ifndef MAX_TOKEN_SIZE
#  define MAX_TOKEN_SIZE 1024
# endif

#endif
