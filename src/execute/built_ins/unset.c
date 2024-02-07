/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:20:14 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/07 16:45:49 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	unset(char **arg)
{
	t_env *head;
	t_env *tail;
	int		i;
	
	i = 1;
	head = shell()->v_env;
	tail = NULL;
	while (head)
	{
		while (arg[i])
		{
			if (ft_strcmp(head->name, arg[i]) == 0)
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
			i++;
		}
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
