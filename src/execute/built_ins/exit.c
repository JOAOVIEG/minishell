/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/14 14:24:47 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

void	exit_shell(int status)
{
	// int i;

	// i = 1;
	// while (arg && arg[i])
	// {
	// 	shell()->status = ft_atoi(arg[i]);
	// 	if (shell()->status < 0)
	// 	{
	// 		printf("minishell: exit: %s: numeric argument required\n", strerror(errno));
	// 		shell()->status = 255;
	// 	}
	// 	i++;
	// }
	free_env();
	shell()->status = status;
	end_shell();
	exit(shell()->status);
}
