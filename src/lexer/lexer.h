/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:00:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/17 13:50:02 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../includes/minishell.h"

typedef enum s_token_type
{
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SINGLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITE_SPACE = ' ',
	CHAR_ESCAPE_SEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEW_LINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	
}	t_token_type;

typedef struct s_lexer_state
{
	char *input;
	size_t current_position;
}	t_lexer_state;

typedef struct s_token
{
	t_token_type type;
	char *value;
}	t_token;




#endif
