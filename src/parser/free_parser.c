/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:20:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/18 17:32:35 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_history(t_history_entry *history)
{
	t_history_entry	*current;
	t_history_entry	*next;

	current = history;
	while (current != NULL)
	{
		next = current->next;
		free(current->command);
		free(current);
		current = next;
	}
}

void	delete_node(t_lst_tokens *node)
{
	free(node->data);
	free(node);
}

void	free_lst_tokens(t_lst_tokens *tokens)
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
		free_lst_tokens(parser->tokens);
	if (parser->q_tokens)
		free_lst_tokens(parser->q_tokens);
	parser->tokens = NULL;
	parser->q_tokens = NULL;
	parser->pipe_count = 0;
	parser->redir_count = 0;
	parser->heredoc_count = 0;
}

void	free_parser(t_parser *parser)
{
	if (parser->tokens)
	{
		free_lst_tokens(parser->tokens);
		parser->tokens = NULL;
	}
	if (parser->q_tokens)
	{
		free_lst_tokens(parser->q_tokens);
		parser->q_tokens = NULL;
	}
	free(parser);
	parser = NULL;
}
