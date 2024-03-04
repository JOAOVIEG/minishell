/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:43 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/04 14:55:17 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	echo(char **cmd)
{
    int	i;
	int n_flag;
	
	n_flag = flag_handle(cmd);
	i = to_print(cmd);
    while (cmd[i])
    {
        if ((printf("%s", cmd[i])) < 0)
            return ((shell()->status = printf("%s", cmd[i])));
        if (cmd[i + 1])
        {
            if ((printf(" ")) < 0)
                return (shell()->status = printf(" "));
        }
        i++;
    }
    if (n_flag)
    {
        if ((printf("\n")) < 0)
            return ((shell()->status = printf("\n")));
    }
    shell()->status = 0;
    return (shell()->status);
}

int	flag_handle(char **cmd)
{
	int i;
	int	j;
	int	n_flag;
	
	i = 1;
	n_flag = 1;
	while (cmd[i])
    {
        if (cmd[i][0] == '-' && cmd[i][1] == 'n')
        {
            j = 2;
            while (cmd[i][j] == 'n')
                j++;
            if (cmd[i][j] == '\0')
            {
                n_flag = 0;
                i++;
            }
            else
                break ;
        }
        else
            break ;
    }
	return (n_flag);
}

int	to_print(char **cmd)
{
	int i;
	int	j;
	
	i = 1;
	while (cmd[i])
    {
        if (cmd[i][0] == '-' && cmd[i][1] == 'n')
        {
            j = 2;
            while (cmd[i][j] == 'n')
                j++;
            if (cmd[i][j] == '\0')
            {
                i++;
            }
            else
                break ;
        }
        else
            break ;
    }
	return (i);
}
