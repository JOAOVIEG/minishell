/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:13:14 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 20:57:21 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	env(void)
{
	t_env	*tmp;

	tmp = shell()->v_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}
