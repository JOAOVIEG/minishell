/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:24:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/06 12:16:53 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == CHAR_WHITESPACE || c == CHAR_TAB || c == CHAR_NEWLINE)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == CHAR_SINGLE_QUOTE || c == CHAR_DOUBLE_QUOTE)
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
			i += 2;
		else if (input[i] == quote_type)
		{
			i++;
			break ;
		}
		else
			i++;
	}
	return (i);
}

int	process_unquoted_token(char *input, int i)
{
	while (!is_whitespace(input[i]) && !is_quote(input[i]) && input[i] != '\0'
		&& input[i] != '|' && input[i] != CHAR_GREATER  && input[i] != CHAR_LESSER)
		i++;
	return (i);
}

int	process_pipe_token(char *input, int i)
{
	if (input[i] == CHAR_PIPE)
		i++;
	return (i);
}

int	process_redirection_token(char *input, int i)
{
    if ( input[i] == CHAR_LESSER)
    {
        i++;
        if (input[i] == CHAR_LESSER) // Check for consecutive '<' characters
            i++;
    }
	else if (input[i] == CHAR_GREATER)
	{
		i++;
		if (input[i] == CHAR_GREATER) // Check for consecutive '>' characters
			i++;
	}
    return (i);
}

// void	process_token(char **tokens, char *input, int *iac)
// {
// 	int	i;
// 	int	start;

// 	i = 0;
// 	if (input[0] == '\0' || (input[0] == ' ' && input[1] == '\0'))
// 	{
// 		tokens[0] = NULL;
// 		return ;
// 	}
// 	while (input[i] != '\0')
// 	{
// 		i = skip_whitespace(input, i);
// 		start = i;
// 		if (input[i] == CHAR_SINGLE_QUOTE || input[i] == CHAR_DOUBLE_QUOTE)
// 			i = process_quoted_token(input, i, input[i]);
// 		else if (input[i] == CHAR_PIPE)
// 			i = process_pipe_token(input, i);
// 		else if (input[i] == CHAR_GREATER || input[i] == CHAR_LESSER)
// 			i = process_redirection_token(input, i);
// 		else
// 			i = process_unquoted_token(input, i);
// 		if (start != i)
// 			tokens[(*iac)++] = create_token(input, start, i);
// 	}
// }

// char	**split_into_tokens(t_lexer *lexer)
// {
// 	int		iac;
// 	char	*input;
// 	char	**tokens;

// 	iac = 0;
// 	input = ft_strdup(lexer->input);
// 	tokens = allocate_memory_for_tokens(lexer->input_size);
// 	process_token(tokens, input, &iac);
// 	tokens[iac] = NULL;
// 	free(input);
// 	return (tokens);
// }