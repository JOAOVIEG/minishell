/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:33:00 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/22 20:20:25 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*build_token(t_lexer *lexer, t_token *token)
{
	int		i;
	int		j;
	int		state;
	char	current;
	int		char_type;

	i = 0;
	j = 0;
	token->value = (char *)malloc(MAX_TOKEN_SIZE);
	state = STATE_IN_GENERAL;
	while (lexer->state.input[i] != '\0')
	{
		current = lexer->state.input[i];
		char_type = get_char_type(current);
		if (state == STATE_IN_GENERAL)
		{
			if (char_type == CHAR_SINGLE_QUOTE)
			{
				state = STATE_IN_SQUOTE;
				token->value[j++] = CHAR_SINGLE_QUOTE;
				token->type = TOKEN;
			}
			else if (char_type == CHAR_DOUBLE_QUOTE)
			{
				state = STATE_IN_DQUOTE;
				token->value[j++] = CHAR_DOUBLE_QUOTE;
				token->type = TOKEN;
			}
			else if (char_type == CHAR_ESCAPE_SEQUENCE)
			{
				token->value[j++] = lexer->state.input[++i];
				token->type = TOKEN;
			}
			else if (char_type == CHAR_GENERAL)
			{
				token->value[j++] = lexer->state.input[i];
				token->type = TOKEN;
			}
			else if (char_type == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					token->value[j] = 0;
					token->next = new_token();
					token = token->next;
					token->value = (char *)malloc(MAX_TOKEN_SIZE);
					j = 0;
				}
			}
			else if (char_type == CHAR_GREATER || char_type == CHAR_LESSER
				|| char_type == CHAR_AMPERSAND || char_type == CHAR_PIPE)
			{
				if (j > 0)
				{
					token->value[j] = 0;
					token->next = new_token();
					token = token->next;
					token->value = (char *)malloc(MAX_TOKEN_SIZE);
					j = 0;
				}
				token->value[0] = char_type;
				token->value[1] = 0;
				token->type = char_type;
				token->next = new_token();
				token = token->next;
				token->value = (char *)malloc(MAX_TOKEN_SIZE);
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->value[j++] = current;
			if (char_type == CHAR_DOUBLE_QUOTE)
				state = STATE_IN_GENERAL;
		}
		else if (state == STATE_IN_SQUOTE)
		{
			token->value[j++] = current;
			if (char_type == CHAR_SINGLE_QUOTE)
				state = STATE_IN_GENERAL;
		}
		if (char_type == CHAR_NULL)
		{
			if (j > 0)
			{
				token->value[j] = 0;
				lexer->ntoks++;
				j = 0;
			}
		}
		i++;
	}
	return (token);
}
