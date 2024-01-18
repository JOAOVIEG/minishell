/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:06:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/18 20:08:23 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void init_lexer_state(t_lx_state *lexer_state, char *input)
{
   
    lexer_state->input = input;
    lexer_state->current_position = 0;
}

t_lexer *init_lexer(void)
{
    t_lexer *lexer= (t_lexer *)malloc(sizeof(t_lexer));
    if(!lexer)
    {
        perror("Error allocating memory for lexer\n");
        exit(EXIT_FAILURE);
    }
    lexer->ntoks = 0;
    lexer->tokens = NULL;
    init_lexer_state(&(lexer->state), NULL);
    return (lexer);
}

void    add_current_position(t_lx_state *lexer_state)
{
        lexer_state->current_position++;
}

// Function to get the current character from the lexer state
char    current_char(const t_lx_state *lexer_state)
{
    return (lexer_state->input[lexer_state->current_position]);
}

void print_input(const  t_lx_state *lexer_state)
{
    while (current_char(lexer_state) != '\0')
    {
       
        printf("Current character: %c\n", current_char(lexer_state));

       // add_current_position(&lexer_state);
    }
}