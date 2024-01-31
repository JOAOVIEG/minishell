/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state_general.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:03:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/31 12:36:48 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_single_quote_char(t_token *token, t_tk_buffer *buffer)
{
	buffer->state = STATE_IN_SQUOTE;
	token->value[buffer->j++] = CHAR_SINGLE_QUOTE;
	token->type = TOKEN;
}
void	handle_double_quote_char(t_token *token, t_tk_buffer *buffer)
{
	buffer->state = STATE_IN_DQUOTE;
	token->value[buffer->j++] = CHAR_DOUBLE_QUOTE;
	token->type = TOKEN;
}

void	handle_escape_sequence_char(t_token *token, t_lexer *lexer,
		t_tk_buffer *buffer)
{
	token->value[buffer->j++] = lexer->state.input[++buffer->i];
	token->type = TOKEN;
}

void	handle_general_char(t_token *token, t_lexer *lexer, t_tk_buffer *buffer)
{
	// if (token->value[buffer->j]  != '\0')
		token->value[buffer->j++] = lexer->state.input[buffer->i];
	token->type = TOKEN;
}

void	handle_whitespace_char(t_token **token, t_tk_buffer *buffer)
{
	if (buffer->j > 0)
	{
		(*token)->value[buffer->j] = 0;
		(*token)->next = new_token();
		*token = (*token)->next;
		(*token)->value = (char *)ft_calloc(1, MAX_TOKEN_SIZE);
		buffer->j = 0;
	}
}

void	handle_special_char(t_token **token, t_tk_buffer *buffer)
{
	if (buffer->j > 0)
	{
		(*token)->value[buffer->j] = 0;
		(*token)->next = new_token();
		*token = (*token)->next;
		(*token)->value = (char *)malloc(MAX_TOKEN_SIZE);
		buffer->j = 0;
	}
	(*token)->value[0] = buffer->char_type;
	(*token)->value[1] = 0;
	(*token)->type = buffer->char_type;
	(*token)->next = new_token();
	*token = (*token)->next;
	(*token)->value = (char *)malloc(MAX_TOKEN_SIZE);
}

t_token	*handle_state_general(t_token *token, t_lexer *lexer,
		t_tk_buffer *buffer)
{
	if (buffer->char_type == CHAR_SINGLE_QUOTE)
		handle_single_quote_char(token, buffer);
	else if (buffer->char_type == CHAR_DOUBLE_QUOTE)
		handle_double_quote_char(token, buffer);
	else if (buffer->char_type == CHAR_ESCAPE_SEQUENCE)
		handle_escape_sequence_char(token, lexer, buffer);
	else if (buffer->char_type == CHAR_GENERAL)
		handle_general_char(token, lexer, buffer);
	else if (buffer->char_type == CHAR_WHITESPACE)
		handle_whitespace_char(&token, buffer);
	else if (buffer->char_type == CHAR_GREATER
		|| buffer->char_type == CHAR_LESSER
		|| buffer->char_type == CHAR_AMPERSAND
		|| buffer->char_type == CHAR_PIPE)
		handle_special_char(&token, buffer);
	return (token);
}


