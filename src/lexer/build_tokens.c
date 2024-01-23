/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:33:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 15:15:43 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*build_token(t_lexer *lexer, t_token *token)
{
	t_tk_buffer	buffer;

	buffer.i = 0;
	buffer.j = 0;
	token->value = (char *)malloc(MAX_TOKEN_SIZE);
	buffer.state = STATE_IN_GENERAL;
	while (lexer->state.input[buffer.i] != '\0')
	{
		buffer.current = lexer->state.input[buffer.i];
		buffer.char_type = get_char_type(buffer.current);
		if (buffer.state == STATE_IN_GENERAL)
			token = handle_state_general(token, lexer, &buffer);
		else if (buffer.state == STATE_IN_DQUOTE)
			token = handle_state_in_dquote(token, lexer, &buffer);
		else if (buffer.state == STATE_IN_SQUOTE)
			token = handle_state_in_squote(token, lexer, &buffer);
		if (buffer.char_type == CHAR_NULL)
		{
			token = handle_null(token, lexer, &buffer);
			break ;
		}
		buffer.i++;
	}
	return (token);
}
