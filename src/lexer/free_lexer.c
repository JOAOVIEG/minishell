/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:47:57 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 18:30:47 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_token_list(t_token *token)
{
    t_token *tmp;

    while (token)
    {
        tmp = token->next;
        if (token->value)
            free(token->value);
        free(token); 
        token = tmp;
    }
}


void	free_lexer(t_lexer *lexer)
{

	if (lexer->tokens)
		free_token_list(lexer->tokens);
	free(lexer);
}