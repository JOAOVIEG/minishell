/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:43 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/01 20:37:07 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == CHAR_WHITESPACE || c == CHAR_TAB || c == CHAR_NEWLINE)
		return (1);
	return (0);
}

char	**split_into_tokens(t_lexer *lexer)
{
	int i;
	int iac;
	char *input;
	char **tokens;
	char quote_type;
	int start;
	int token_length;

	iac = 0;
	tokens = ft_calloc((lexer->input_size > 0 ? lexer->input_size : 1),
			sizeof(char *));
	input = ft_strdup(lexer->input);
	i = 0;
	while (input[i] != '\0')
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue ;
		}
		start = i;
		if (input[i] == CHAR_SINGLE_QUOTE || input[i] == CHAR_DOUBLE_QUOTE)
		{
			quote_type = input[i++];
			while (input[i] != '\0')
			{
				if (input[i] == CHAR_ESCAPE_SEQUENCE
					&& quote_type == CHAR_DOUBLE_QUOTE)
				{
					i += 2;
					continue ;
				}
				if (input[i] == quote_type)
				{
					i++;
					break ;
				}
				i++;
			}
		}
		else
		{
			while (!is_whitespace(input[i]) && input[i] != '\0')
				i++;
		}
		token_length = i - start;
		tokens[iac] = ft_calloc(token_length + 1, sizeof(char));
		ft_memcpy(tokens[iac], &input[start], token_length);
		tokens[iac][token_length] = '\0';
		iac++;
	}
	tokens[iac] = NULL;
	free(input);
	return (tokens);
}