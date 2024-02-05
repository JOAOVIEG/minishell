/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:20:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/05 19:17:15 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node(t_lst_tokens *node)
{
	free(node->data);
	free(node);
}

void	free_parser_tokens(t_lst_tokens *tokens)
{
	t_lst_tokens	*current;
	t_lst_tokens	*next;

	current = tokens;
	while (current != NULL)
	{
		next = current->next;
		delete_node(current);
		current = next;
	}
}

void	reset_parser(t_parser *parser)
{
	if (parser->tokens)
		free_parser_tokens(parser->tokens);
	parser->tokens = NULL;
}
void	free_parser(t_parser *parser)
{
	if (parser->tokens)
		free_parser_tokens(parser->tokens);
	free(parser);
}