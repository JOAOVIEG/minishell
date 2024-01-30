/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:58:59 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 18:34:20 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		perror("Error allocating memory for tokens\n");
		exit(EXIT_FAILURE);
	}
	token_init(token);
	return (token);
}


t_token *create_new_token(char *value) {
    t_token *token = malloc(sizeof(t_token));
    if (token == NULL) {
        // Handle error
        return NULL;
    }

    // Allocate enough space for the string and the null terminator
    token->value = malloc(strlen(value) + 1);
    if (token->value == NULL) {
        // Handle error
        free(token);
        return NULL;
    }

    // Copy the string and add the null terminator
    strcpy(token->value, value);
    token->value[strlen(value)] = '\0';

    token->next = NULL;

    return token;
}