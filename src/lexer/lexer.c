/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:06:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/05 18:51:18 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*init_lexer(void)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
	{
		perror("Error allocating memory for lexer\n");
		exit(EXIT_FAILURE);
	}
	lexer->ntoks = 0;
	lexer->input = NULL;
	lexer->tokens = NULL;
	lexer->input_size = 0;
	return (lexer);
}

void	tokenize_input(char *input, t_lexer *lexer)
{
	int	i;

	lexer->input = ft_strdup(input);
	lexer->input_size = ft_strlen(lexer->input);
	lexer->tokens = split_into_tokens(lexer);
	i = 0;
	while (lexer->tokens[i] != NULL)
	{
		//printf("Token: %s\n", lexer->tokens[i]);
		lexer->ntoks++;
		i++;
	}
	//printf("Number of tokens: %d\n", lexer->ntoks);
	free(input);
}
