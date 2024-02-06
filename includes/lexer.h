/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:00:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/06 14:38:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_char_type
{
	CHAR_PIPE = '|',
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

}			t_char_type;

typedef struct s_lexer
{
	int		ntoks;
	char	*input;
	size_t	input_size;
	char	**tokens;
}			t_lexer;

t_lexer		*init_lexer(void);
void		tokenize_input(char *input, t_lexer *lexer);
int			is_whitespace(char c);
int			skip_whitespace(char *input, int i);
char		**allocate_memory_for_tokens(int input_size);
char		*create_token(char *input, int start, int end);
int			process_pipe_token(char *input, int i);
int			process_quoted_token(char *input, int i, char quote_type);
int			process_unquoted_token(char *input, int i);

char		**split_into_tokens(t_lexer *lexer);

// free functions
void		reset_lexer(t_lexer *lexer);
void		free_lexer(t_lexer *lexer);
void		free_lexer_tokens(t_lexer *lexer);
#endif
