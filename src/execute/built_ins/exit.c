/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:51 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/22 12:22:10 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exit_shell(char *arg)
{
	if (arg)
	{
		shell()->status = ft_atoi(arg);
		if (shell()->status < 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", strerror(errno));
			shell()->status = 255;
		}
	}
	free_env();
	exit(shell()->status);
}

void	free_env(void)
{
	while (shell()->v_env)
	{
		free(shell()->v_env->name);
		free(shell()->v_env->value);
		shell()->v_env = shell()->v_env->next;
	}
	free(shell()->v_env);
}
