/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ultils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 09:51:05 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/12 09:52:01 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_token_queue(t_token_queue *queue)
{
	t_lst_tokens	*current;
	t_lst_tokens	*next;

	current = queue->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	queue->head = NULL;
	queue->tail = NULL;
}

void	clean_buffer(t_buffer *buffer)
{
	clean_token_queue(&buffer->cmds);
	clean_token_queue(&buffer->heredocs);
	clean_token_queue(&buffer->redir_files);
}
