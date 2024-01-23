/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_state_in_dquote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:28:18 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 11:08:55 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_state_in_dquote(t_token *token, t_lexer *lexer,
		t_tk_buffer *buffer)
{
	(void)lexer;
	token->value[buffer->j++] = buffer->current;
	if (buffer->char_type == CHAR_DOUBLE_QUOTE)
		buffer->state = STATE_IN_GENERAL;
	return (token);
}