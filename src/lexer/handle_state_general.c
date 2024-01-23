 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state_general.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:03:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 10:17:48 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_state_general(t_token *token, t_lexer *lexer,
		t_tk_buffer *buffer)
{
	if (buffer->char_type == CHAR_SINGLE_QUOTE)
	{
		buffer->state = STATE_IN_SQUOTE;
		token->value[buffer->j++] = CHAR_SINGLE_QUOTE;
		token->type = TOKEN;
	}
	else if (buffer->char_type == CHAR_DOUBLE_QUOTE)
	{
		buffer->state = STATE_IN_DQUOTE;
		token->value[buffer->j++] = CHAR_DOUBLE_QUOTE;
		token->type = TOKEN;
	}
	else if (buffer->char_type == CHAR_ESCAPE_SEQUENCE)
	{
		token->value[buffer->j++] = lexer->state.input[++buffer->i];
		token->type = TOKEN;
	}
	else if (buffer->char_type == CHAR_GENERAL)
	{
		token->value[buffer->j++] = lexer->state.input[buffer->i];
		token->type = TOKEN;
	}
	else if (buffer->char_type == CHAR_WHITESPACE)
	{
		if (buffer->j > 0)
		{
			token->value[buffer->j] = 0;
			token->next = new_token();
			token = token->next;
			token->value = (char *)malloc(MAX_TOKEN_SIZE);
			buffer->j = 0;
		}
	}
	else if (buffer->char_type == CHAR_GREATER || buffer->char_type == CHAR_LESSER
        || buffer->char_type == CHAR_AMPERSAND || buffer->char_type == CHAR_PIPE)
    {
        if (buffer->j > 0)
        {
            token->value[buffer->j] = 0;
            token->next = new_token();
            token = token->next;
            token->value = (char *)malloc(MAX_TOKEN_SIZE);
            buffer->j = 0;
        }
        token->value[0] = buffer->char_type;
        token->value[1] = 0;
        token->type = buffer->char_type;
        token->next = new_token();
        token = token->next;
        token->value = (char *)malloc(MAX_TOKEN_SIZE);
    }
	return (token);

}
