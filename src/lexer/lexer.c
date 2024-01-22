/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:06:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/22 18:07:14 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_lexer_state(t_lx_state *lexer_state, char *input)
{
	lexer_state->input = input;
	lexer_state->current_position = 0;
}

t_lexer	*init_lexer(void)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
	{
		perror("Error allocating memory for lexer\n");
		exit(EXIT_FAILURE);
	}
	lexer->ntoks = 0;
	lexer->tokens = NULL;
	init_lexer_state(&(lexer->state), NULL);
	return (lexer);
}

void	add_current_position(t_lx_state *lexer_state)
{
	lexer_state->current_position++;
}

// Function to get the current character from the lexer state
char	current_char(const t_lx_state *lexer_state)
{
	return (lexer_state->input[lexer_state->current_position]);
}

void	print_input(const t_lx_state *lexer_state)
{
	while (current_char(lexer_state) != '\0')
	{
		printf("Current character: %c\n", current_char(lexer_state));
		// add_current_position(&lexer_state);
	}
}

void	tokenize_pipe(t_lexer *lexer)
{
	(void)lexer;
	printf("Need implement the function to tokenize a PIPE\n");
}

void	tokenize_whitespace(t_lexer *lexer)
{
	(void)lexer;
	printf("Need implement the function to tokenize a WHITESPACE\n");
}

void	token_init(t_token *token)
{
	token->type = TOKEN;
	token->value = NULL;
	token->precedence = 0;
	token->next = NULL;
}

int	get_char_type(char c)
{
	if (c == CHAR_PIPE)
		return (CHAR_PIPE);
	else if (c == CHAR_AMPERSAND)
		return (CHAR_AMPERSAND);
	else if (c == CHAR_SINGLE_QUOTE)
		return (CHAR_SINGLE_QUOTE);
	else if (c == CHAR_DOUBLE_QUOTE)
		return (CHAR_DOUBLE_QUOTE);
	else if (c == CHAR_WHITESPACE)
		return (CHAR_WHITESPACE);
	else if (c == CHAR_ESCAPE_SEQUENCE)
		return (CHAR_ESCAPE_SEQUENCE);
	else if (c == CHAR_TAB)
		return (CHAR_TAB);
	else if (c == CHAR_NEWLINE)
		return (CHAR_NEWLINE);
	else if (c == CHAR_GREATER)
		return (CHAR_GREATER);
	else if (c == CHAR_LESSER)
		return (CHAR_LESSER);
	else if (c == CHAR_NULL)
		return (CHAR_NULL);
	else
		return (CHAR_GENERAL);
}

void	tokenize_input(t_lexer *lexer)
{
	char	current;
	int		i;
	int		j;
	int		state;
	int		char_type;
	t_token	*token;

	i = 0;
	j = 0;
	state = STATE_IN_GENERAL;
	lexer->tokens = (t_token *)malloc(sizeof(t_token));
	if (!lexer->tokens)
	{
		perror("Error allocating memory for tokens\n");
		exit(EXIT_FAILURE);
	}
	token = lexer->tokens;
	token_init(token);
	token->value = (char *)malloc(MAX_TOKEN_SIZE);
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
					token->next = (t_token *)malloc(sizeof(t_token));
					if (!token->next)
					{
						perror("Error allocating memory for tokens\n");
						exit(EXIT_FAILURE);
					}
					token = token->next;
					token_init(token);
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
					token->next = (t_token *)malloc(sizeof(t_token));
					if (!token->next)
					{
						perror("Error allocating memory for tokens\n");
						exit(EXIT_FAILURE);
					}
					token = token->next;
					token_init(token);
					token->value = (char *)malloc(MAX_TOKEN_SIZE);
					j = 0;
				}
				token->value[0] = char_type;
				token->value[1] = 0;
				token->type = char_type;
				token->next = (t_token *)malloc(sizeof(t_token));
				if (!token->next)
				{
					perror("Error allocating memory for tokens\n");
					exit(EXIT_FAILURE);
				}
				token = token->next;
				token_init(token);
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
	// my code not are incrementig the number of tokens
	// printf("Number of tokens: %d\n", lexer->ntoks);
	printf("Tokens:\n");
	token = lexer->tokens;
	while (token != NULL)
	{
		printf("Token: %s\n", token->value);
		token = token->next;
	}
}
