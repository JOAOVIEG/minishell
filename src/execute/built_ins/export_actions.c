/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:43:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/27 14:10:21 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// int	choose_export_action(t_exp_buff *exp_buff, t_env *env, t_env *new)
// {
// 	env = NULL;
// 	(void)new;
// 	if (exp_buff->name[0] == '_' && exp_buff->name[1] == '\0')
// 	{
// 		export_does_nothing(exp_buff);
// 		return (1);
// 	}
// 	if (is_invalid_variable(exp_buff->name))
// 	{
// 		handle_export_var_error(exp_buff);
// 		return (1);
// 	}
// 	if (exp_buff->name && ft_strchr(exp_buff->name, '+'))
// 	{
// 		exp_buff->name = ft_strtrim(exp_buff->name, "+");
// 		concatonate_and_update(env, new, exp_buff->name, exp_buff->value);
// 	}
// 	else
// 		updt_envl(exp_buff, env, new);
// 	return (0);
// }
