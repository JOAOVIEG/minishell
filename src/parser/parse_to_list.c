/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:41:27 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/02 18:58:34 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void print_list(t_lst_tokens *head)
{
    t_lst_tokens *current = head;
    printf("List of tokens:\n");
    while (current != NULL)
    {
        printf("%s\n", current->data);
        current = current->next;
    }
}

t_lst_tokens *new_node(char *data)
{
    t_lst_tokens *node = ft_calloc(1, sizeof(t_lst_tokens));
    if (!node)
        return NULL;

    // Allocate memory for data and copy the content
    node->data = ft_strdup(data);
    if (!node->data)
    {
        free(node);
        return NULL;
    }

    node->next = NULL;
    return node;
}


void add_to_end(t_lst_tokens **head, char *data)
{
    t_lst_tokens *newNode = new_node(data);
    if (!newNode)
        return;
    if (!*head)
    {
        *head = newNode;
        return;
    }
    t_lst_tokens *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}
void parse_to_list(t_lexer *lexer, t_parser *parser)
{
    t_lst_tokens *head = NULL;
    int i = 0;
    while (lexer->tokens[i] != NULL)
    {
        add_to_end(&head, lexer->tokens[i]);
        i++;
    }
    parser->tokens = head;
    free_lexer_tokens(lexer);
}