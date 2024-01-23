/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:06:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 17:27:49 by wiferrei         ###   ########.fr       */
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
	t_token	*token;
	int i;

	lexer->tokens = new_token();
	token = lexer->tokens;
	token_init(token);
	token = build_token(lexer, token);
	printf("Tokens:\n");
	token = lexer->tokens;
	i = 0;
	while (token != NULL)
	{
		printf("Token: %s\n", token->value);
		token = token->next;
		i++;
	}
	lexer->ntoks = i;
	printf("Number of tokens: %d\n", lexer->ntoks);
	// This function need change to return a list of tokens
}
