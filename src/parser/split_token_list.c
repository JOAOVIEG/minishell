/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:40:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 13:56:58 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_new_node(t_token *current)
{
	t_token	*node;

	node = new_token();
	node->value = ft_strdup(current->value);
	node->next = NULL;
	return (node);
}

void	split_left(t_token **current, t_token **left, t_token **left_tail,
		char *delimiter)
{
	t_token	*left_node;

	while (*current != NULL)
	{
		if (ft_strcmp((*current)->value, delimiter) == 0)
		{
			*current = (*current)->next;
			break ;
		}
		left_node = create_new_node(*current);
		if (*left == NULL)
		{
			*left = left_node;
			*left_tail = left_node;
		}
		else
		{
			(*left_tail)->next = left_node;
			*left_tail = left_node;
		}
		*current = (*current)->next;
	}
}

void	split_right(t_token **current, t_token **right, t_token **right_tail)
{
	t_token	*right_node;

	while (*current != NULL)
	{
		right_node = create_new_node(*current);
		if (*right == NULL)
		{
			*right = right_node;
			*right_tail = right_node;
		}
		else
		{
			(*right_tail)->next = right_node;
			*right_tail = right_node;
		}
		*current = (*current)->next;
	}
}

void	split_token_list(t_token *tokens, t_parser *parser, char *delimiter)
{
	t_token	*current;
	t_token	*left;
	t_token	*right;
	t_token	*left_tail;
	t_token	*right_tail;

	current = tokens;
	left = NULL;
	right = NULL;
	left_tail = NULL;
	right_tail = NULL;
	split_left(&current, &left, &left_tail, delimiter);
	split_right(&current, &right, &right_tail);
	parser->buffer->left = left;
	parser->buffer->right = right;
}
