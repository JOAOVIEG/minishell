/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:00:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/01 20:22:51 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_token_type
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

}			t_token_type;

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
char		**split_into_tokens(t_lexer *lexer);

// free functions
void		free_lexer(t_lexer *lexer);
void		free_tokens(t_lexer *lexer);

#endif
