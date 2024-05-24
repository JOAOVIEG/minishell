/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_process_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:22:41 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/03 16:40:31 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*trim_and_join_args(char **args, int iac)
{
	char	*tmp;
	char	*new_arg;

	if (args[iac][ft_strlen(args[iac]) - 1] == '_')
	{
		tmp = args[iac];
		args[iac] = ft_strtrim(args[iac], "_");
		free(tmp);
	}
	new_arg = ft_strjoin(args[iac], args[iac + 1]);
	free(args[iac]);
	free(args[iac + 1]);
	return (new_arg);
}

void	shift_args_down(char **args, int start)
{
	int	j;

	j = start;
	while (args[j])
	{
		args[j] = args[j + 1];
		j++;
	}
}

char	**process_env_variables(char **args)
{
	int	iac;

	iac = 1;
	while (args[iac])
	{
		if ((args[iac][ft_strlen(args[iac]) - 1] == '_') && args[iac + 1])
		{
			args[iac] = trim_and_join_args(args, iac);
			shift_args_down(args, iac + 1);
		}
		iac++;
	}
	return (args);
}
