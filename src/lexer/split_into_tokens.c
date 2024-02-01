/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:43 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/01 20:59:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == CHAR_WHITESPACE || c == CHAR_TAB || c == CHAR_NEWLINE)
		return (1);
	return (0);
}

int	skip_whitespace(char *input, int i)
{
	while (is_whitespace(input[i]))
		i++;
	return (i);
}

int	process_quoted_token(char *input, int i, char quote_type)
{
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == CHAR_ESCAPE_SEQUENCE && quote_type == CHAR_DOUBLE_QUOTE)
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
	return (i);
}

int	process_unquoted_token(char *input, int i)
{
	while (!is_whitespace(input[i]) && input[i] != '\0')
		i++;
	return (i);
}

char	*create_token(char *input, int start, int end)
{
	int		token_length;
	char	*token;

	token_length = end - start;
	token = ft_calloc(token_length + 1, sizeof(char));
	ft_memcpy(token, &input[start], token_length);
	token[token_length] = '\0';
	return (token);
}

char	**split_into_tokens(t_lexer *lexer)
{
	int		i;
	int		iac;
	int		start;
	char	*input;
	char	**tokens;

	i = 0;
	iac = 0;
	input = ft_strdup(lexer->input);
	tokens = ft_calloc((lexer->input_size > 0 ? lexer->input_size : 1),
			sizeof(char *));
	while (input[i] != '\0')
	{
		i = skip_whitespace(input, i);
		start = i;
		if (input[i] == CHAR_SINGLE_QUOTE || input[i] == CHAR_DOUBLE_QUOTE)
			i = process_quoted_token(input, i, input[i]);
		else
			i = process_unquoted_token(input, i);
		tokens[iac++] = create_token(input, start, i);
	}
	tokens[iac] = NULL;
	free(input);
	return (tokens);
}
