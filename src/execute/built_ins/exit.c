/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:58:07 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/02 10:34:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exit_shell(int status)
{
	free_env();
	shell()->status = status;
	end_shell();
	exit(shell()->status);
}

int	ft_in_is_digit(char *in)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	if (!ft_isdigit(in[i]) && in[i] != '-' && in[i] != '+')
	{
		shell()->status = 2;
		return (0);
	}
	i++;
	if (in[i] == '-')
	{
		flag = 1;
		i++;
	}
	while (in[i])
	{
		if (flag)
		{
			shell()->status = 2;
			return (0);
		}
		else if (!ft_isdigit(in[i]))
		{
			shell()->status = 2;
			return (0);
		}
		i++;
	}
	return (1);
}

long long int	ft_atol(const char *av)
{
	int				sign;
	long long int	integer;

	sign = 1;
	integer = 0;
	if (*(char *)av == '-' || *(char *)av == '+')
	{
		if (*(char *)av == '-')
			sign = -1;
		av++;
	}
	while (*(char *)av && *(char *)av >= '0' && *(char *)av <= '9')
	{
		integer = (integer * 10) + *(char *)av - '0';
		av++;
	}
	return (sign * integer);
}

void	ft_exit(char **arg)
{
	if (!arg[1])
		shell()->status = EXIT_SUCCESS;
	else if (!arg[2])
	{
		if (!ft_in_is_digit(arg[1]))
			status_error(arg[1], "numeric argument required", STDERR_FILENO);
		else
			shell()->status = ft_atol(arg[1]);
	}
	else
	{
		status_error("minishell", "too many arguments", STDERR_FILENO);
		shell()->status = 1;
	}
	exit_shell(shell()->status);
}
