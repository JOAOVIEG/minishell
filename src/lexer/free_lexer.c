/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:47:57 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/01 20:19:58 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer->tokens[i] != NULL)
	{
		free(lexer->tokens[i]);
		i++;
	}
	lexer->ntoks = 0;
	lexer->input_size = 0;
	free(lexer->input);
	free(lexer->tokens);
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer->input)
	{
		free(lexer->input);
		lexer->input = NULL;
	}
	free(lexer);
}