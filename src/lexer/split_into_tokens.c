/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:23:43 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/17 19:14:28 by wiferrei         ###   ########.fr       */
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

void	process_token(char **tokens, char *input, int *iac)
{
	int	i;
	int	start;

	i = 0;
	if (input[0] == '\0' || (input[0] == ' ' && input[1] == '\0'))
	{
		tokens[0] = NULL;
		return ;
	}
	while (input[i] != '\0')
	{
		i = skip_whitespace(input, i);
		start = i;
		if (input[i] == CHAR_SINGLE_QUOTE || input[i] == CHAR_DOUBLE_QUOTE)
			i = process_quoted_token(input, i, input[i]);
		else if (input[i] == CHAR_PIPE)
			i = process_pipe_token(input, i);
		else if (input[i] == CHAR_GREATER || input[i] == CHAR_LESSER)
			i = process_redirection_token(input, i);
		else
			i = process_unquoted_token(input, i);
		if (start != i)
			tokens[(*iac)++] = create_token(input, start, i);
	}
}
char	*preprocess_input(const char *input)
{
	char	*new_input;
	int		i;
	int		j;

	new_input = malloc((strlen(input) * 2 + 1) * sizeof(char));
	if (!new_input)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '=' && input[i + 1] == ' ' && (input[i + 2] == '\''
				|| input[i + 2] == '\"'))
		{
			new_input[j++] = '=';
			new_input[j++] = '_';
			new_input[j++] = input[i + 2];
			i += 3;
		}
		else
		{
			new_input[j++] = input[i++];
		}
	}
	new_input[j] = '\0';
	return (new_input);
}

char	**split_into_tokens(t_lexer *lexer)
{
	int		iac;
	char	*input;
	char	**tokens;

	iac = 0;
	input = preprocess_input(lexer->input);
	tokens = allocate_memory_for_tokens(lexer->input_size);
	process_token(tokens, input, &iac);
	tokens[iac] = NULL;
	free(input);
	return (tokens);
}
