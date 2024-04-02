/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/02 08:49:02 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(char **arg)
{
	t_exp_buff	*exp_data;

	if (!arg[1])
	{
		display_exp_var(shell()->v_env);
		shell()->status = EXIT_SUCCESS;
		return ;
	}
	exp_data = get_exp_data(arg);
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
}
