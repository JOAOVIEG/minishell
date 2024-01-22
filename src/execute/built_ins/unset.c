/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:03:00 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/22 14:37:08 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset(char *arg)
{
	t_env *head;
	t_env *tail;

	head = shell()->v_env;
	tail = NULL;

	while (head)
	{
		if (ft_strcmp(head->name, arg) == 0)
		{
			if (tail)
				tail->next = head->next;
			else
				shell()->v_env = head->next;
			free(head->name);
			head->name = NULL;
			free(head->next);
			head->next = NULL;
			free(head);
			head = NULL;
			shell()->status = 0;
			break ;
		}
		tail = head;
		head = head->next;
	}
}
