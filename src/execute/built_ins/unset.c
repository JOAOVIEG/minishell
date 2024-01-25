/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:20:14 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/25 15:21:04 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

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
			unset_var(head);
			shell()->status = 0;
			return ;
		}
		tail = head;
		head = head->next;
	}
	printf("minishell: %s\n", strerror(errno));
	shell()->status = 1;
}

t_env	*unset_var(t_env *head)
{
	free(head->name);
	head->name = NULL;
	free(head->value);
	head->value = NULL;
	free(head);
	head = NULL;
	return (head);
}
