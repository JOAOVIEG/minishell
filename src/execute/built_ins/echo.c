/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:43 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/15 15:03:39 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/minishell.h"

void	echo(char **cmd)
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
		printf("%s", cmd[i]);
		if (cmd[i + 1] && (cmd + i + 1))
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
