/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state_in_squote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:12:41 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 15:17:02 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_state_in_squote(t_token *token, t_lexer *lexer,
		t_tk_buffer *buffer)
{
	(void)lexer;
	token->value[buffer->j++] = buffer->current;
	if (buffer->char_type == CHAR_SINGLE_QUOTE)
		buffer->state = STATE_IN_GENERAL;
	return (token);
}