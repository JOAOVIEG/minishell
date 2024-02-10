/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:28:42 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/10 16:39:40 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	end_shell();
}
