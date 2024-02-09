/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:20:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/07 16:10:51 by wiferrei         ###   ########.fr       */
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

// void	free_buffer(t_pbuffer *buffer)
// {
// 	if (!buffer)
// 		return ;
// 	if (buffer->head)
// 		free_parser_tokens(buffer->head);
// 	if (buffer->lst_after)
// 		free_parser_tokens(buffer->lst_after);
// 	if (buffer->lst_before)
// 		free_parser_tokens(buffer->lst_before);
// 	free(buffer);
// }

void	reset_parser(t_parser *parser)
{
	if (parser->tokens)
		free_parser_tokens(parser->tokens);
	parser->tokens = NULL;
	parser->pipe_count = 0;
}
void	free_parser(t_parser *parser)
{
	if (parser->tokens)
		free_parser_tokens(parser->tokens);
	free(parser);
}