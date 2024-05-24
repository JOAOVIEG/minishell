/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:53:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/03 11:50:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_invalid_variable(char *name)
{
	int	i;

	if (name == NULL || name[0] == '\0')
		return (1);
	if (ft_isdigit(name[0]))
		return (1);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if (name[i] != '+' || name[i + 1] != '\0')
				return (1);
		}
		i++;
	}
	i = 0;
	return (0);
}

bool	verify_env_name(t_exp_buff *data)
{
	if (is_invalid_variable(data->name))
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(data->name, STDERR_FILENO);
		if (data->equal)
			ft_putstr_fd(data->equal, STDERR_FILENO);
		if (data->value)
			ft_putstr_fd(data->value, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
