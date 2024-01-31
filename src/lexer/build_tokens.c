/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:33:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/31 13:34:20 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*build_token(t_lexer *lexer, t_token *token)
{
	t_tk_buffer	buffer;

	buffer.i = 0;
	buffer.j = 0;
	token->value = (char *)calloc(1, MAX_TOKEN_SIZE);
	token->value[MAX_TOKEN_SIZE - 1] = '\0';
	buffer.state = STATE_IN_GENERAL;
	while (lexer->state.input[buffer.i] != '\0')
	{
		// printf("CHAR BUILT TOKEN: {%c}\n", lexer->state.input[buffer.i]);
		buffer.current = lexer->state.input[buffer.i];
		buffer.char_type = get_char_type(buffer.current);
		if (buffer.state == STATE_IN_GENERAL)
		{
			token = handle_state_general(token, lexer, &buffer);
			// printf("\033[0;31m]");
			// printf("AqUI TOKEN: {%c}\n", token->value[buffer.j]);
			// printf("\033[0m");
			
		}
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
	// printf("DEPOIS DO WHILE: {%s}\n\n", token->value);
	// buffer.i = 0;
	// buffer.j = 0;
	// buffer.state = 0;
	// buffer.char_type = 0;
	// buffer.current = 0;
	return (token);
}
