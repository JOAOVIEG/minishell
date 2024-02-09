/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:47:57 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/06 15:50:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_lexer(t_lexer *lexer)
{
	if (lexer->tokens)
		free_lexer_tokens(lexer);
	lexer->tokens = NULL;
	lexer->input = NULL;
	lexer->input_size = 0;
	lexer->ntoks = 0;
}

void	free_lexer_tokens(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->tokens[i] != NULL)
	{
		free(lexer->tokens[i]);
		lexer->tokens[i] = NULL;
		i++;
	}
	lexer->ntoks = 0;
	lexer->input_size = 0;
	free(lexer->input);
	lexer->input = NULL;
	free(lexer->tokens);
	lexer->tokens = NULL;
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer->input)
	{
		free(lexer->input);
		lexer->input = NULL;
	}
	if (lexer->tokens)
		free_lexer_tokens(lexer);
	if (lexer)
		free(lexer);
}
