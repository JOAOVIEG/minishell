/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:43 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/06 15:45:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**allocate_memory_for_tokens(int input_size)
{
	int	token_size;

	if (input_size > 0)
		token_size = input_size + 1;
	else
		token_size = 1;
	return (ft_calloc(token_size, sizeof(char *)));
}

char	**split_into_tokens(t_lexer *lexer)
{
	int		i;
	int		iac;
	char	*input;
	char	**tokens;
	int		start;

	i = 0;
	iac = 0;
	input = ft_strdup(lexer->input);
	tokens = allocate_memory_for_tokens(lexer->input_size);
	if (input[0] == '\0' || (input[0] == ' ' && input[1] == '\0'))
	{
		tokens[0] = NULL;
		free(input);
		return (tokens);
	}
	while (input[i] != '\0')
	{
		i = skip_whitespace(input, i);
		start = i;
		if (input[i] == CHAR_SINGLE_QUOTE || input[i] == CHAR_DOUBLE_QUOTE)
			i = process_quoted_token(input, i, input[i]);
		else if (input[i] == CHAR_PIPE)
			i = process_pipe_token(input, i);
		else
			i = process_unquoted_token(input, i);
		if (start != i)
			tokens[iac++] = create_token(input, start, i);
	}
	tokens[iac] = NULL;
	free(input);
	return (tokens);
}

// this function should be refactored 
