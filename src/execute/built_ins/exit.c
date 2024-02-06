/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:28:42 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/06 14:02:15 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

void	exit_shell(char **arg)
{
	int i;

	i = 1;
	while (arg && arg[i])
	{
		shell()->status = ft_atoi(arg[i]);
		if (shell()->status < 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", strerror(errno));
			shell()->status = 255;
		}
		i++;
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
