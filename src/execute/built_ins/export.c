/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/22 17:27:01 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	choose_exp_action(t_exp_buff *exp_data)
{
	t_env	*env_list;

	env_list = shell()->v_env;
	if (ft_strcmp(exp_data->equal, "+=") == 0)
		env_list = concatenate_envl(env_list, exp_data);
	else if (ft_strcmp(exp_data->equal, "=") == 0)
		env_list = update_envl(env_list, exp_data);
	shell()->v_env = env_list;
	shell()->status = EXIT_SUCCESS;
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
		choose_exp_action(exp_data);
		clean_exp_buff(exp_data);
		i++;
	}
}
