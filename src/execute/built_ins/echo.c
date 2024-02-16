/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:43 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/16 14:38:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/minishell.h"

int	echo(char **cmd)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	i = 1;
	if (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd && cmd[i])
	{
		if ((printf("%s", cmd[i])) < 0)
			return ((shell()->status = printf("%s", cmd[i])));
		if (cmd[i + 1] && (cmd + i + 1))
		{
			if ((printf(" ")) < 0)
				return (shell()->status = printf(" "));
		}
		i++;
	}
	if (newline)
	{
		if ((printf("\n")) < 0)
			return ((shell()->status = printf("\n")));
	}
	shell()->status = 0;
	return (shell()->status);
}
