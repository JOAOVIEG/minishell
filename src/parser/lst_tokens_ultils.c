/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tokens_ultils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:04:13 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/14 17:36:28 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_tokenadd_back(t_lst_tokens **lst, t_lst_tokens **tail,
		t_lst_tokens *new)
{
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		*tail = new;
	}
}

int	lst_token_size(t_lst_tokens *tokens)
{
	int count;
	t_lst_tokens *current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}