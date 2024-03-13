/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/13 20:11:34 by wiferrei         ###   ########.fr       */
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
	// 		printf("minishell: exit: %s: numeric argument required\n",strerror(errno));
	// 		shell()->status = 255;
	// 	}
	// 	i++;
	// }
	free_env();
	shell()->status = status;
	end_shell();
}
