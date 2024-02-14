/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:41:27 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/14 16:36:05 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(t_lst_tokens *head)
{
	t_lst_tokens	*current;

	current = head;
	printf("List of tokens:\n");
	while (current != NULL)
	{
		printf("token: %s\n", current->data);
		printf("type: %d\n", current->type);
		current = current->next;
	}
}

t_lst_tokens	*new_node(char *data)
{
	t_lst_tokens	*node;

	node = (t_lst_tokens *)ft_calloc_memory(1, sizeof(t_lst_tokens));
	node->data = ft_strdup(data);
	if (!node->data)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	add_to_end(t_lst_tokens **head, char *data)
{
	t_lst_tokens	*node;
	t_lst_tokens	*temp;

	node = new_node(data);
	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

void	count_pipes(t_parser *parser)
{
	t_lst_tokens	*current;

	current = parser->tokens;
	while (current != NULL)
	{
		if (current->type == TYPE_PIPE)
			parser->pipe_count++;
		current = current->next;
	}
}
void	parse_to_list(t_lexer *lexer, t_parser *parser)
{
	t_lst_tokens	*head;
	int				i;

	head = NULL;
	i = 0;
	while (lexer->tokens[i] != NULL)
	{
		add_to_end(&head, lexer->tokens[i]);
		i++;
	}
	parser->tokens = head;
	get_token_type(parser->tokens);
	count_pipes(parser);
	free_lexer_tokens(lexer);
}
