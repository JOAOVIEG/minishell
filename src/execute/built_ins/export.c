/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/03 16:06:50 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**process_env_variables(char **args)
{
	int		iac;
	char	*new_arg;
	int		j;
	char	*tmp;

	iac = 1;
	while (args[iac])
	{
		if ((args[iac][ft_strlen(args[iac]) - 1] == '_') && args[iac + 1])
		{
			if (args[iac][ft_strlen(args[iac]) - 1] == '_')
			{
				tmp = args[iac];
				args[iac] = ft_strtrim(args[iac], "_");
				free(tmp);
			}
			new_arg = ft_strjoin(args[iac], args[iac + 1]);
			free(args[iac]);
			free(args[iac + 1]);
			args[iac] = new_arg;
			j = iac + 1;
			while (args[j])
			{
				args[j] = args[j + 1];
				j++;
			}
		}
		iac++;
	}
	return (args);
}

void	export(char **arg)
{
	t_exp_buff	*exp_data;
	char		**args;
	int			i;

	if (!arg[1])
	{
		display_exp_var(shell()->v_env);
		shell()->status = EXIT_SUCCESS;
		return ;
	}
	i = 1;
	args = process_env_variables(arg);
	while (arg[i])
	{
		exp_data = get_exp_data(args[i]);
		if (!exp_data || !exp_data->equal || !verify_env_name(exp_data))
		{
			shell()->status = EXIT_FAILURE;
			clean_exp_buff(exp_data);
			return ;
		}
		if (ft_strcmp(exp_data->equal, "+=") == 0)
			shell()->v_env = concatenate_envl(shell()->v_env, exp_data);
		else if (ft_strcmp(exp_data->equal, "=") == 0)
			shell()->v_env = update_envl(shell()->v_env, exp_data);
		clean_exp_buff(exp_data);
		shell()->status = EXIT_SUCCESS;
		i++;
	}
}
