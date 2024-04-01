/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_actions_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:27:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/27 14:10:31 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// void	export_does_nothing(t_exp_buff *exp_buff)
// {
// 	shell()->status = EXIT_SUCCESS;
// 	clean_exp_buff(exp_buff);
// }

// void	handle_export_var_error(t_exp_buff *exp_buff)
// {
// 	printf("minishell: export: `%s': not a valid identifier\n", exp_buff->name);
// 	shell()->status = STDERR_FILENO;
// 	clean_exp_buff(exp_buff);
// }

// void	concatonate_and_update(t_env *env, t_env *new, char *name, char *value)
// {
// 	t_env	*head;
// 	t_env	*v_env;

// 	(void)env;
// 	head = env;
// 	while (env->next != NULL)
// 	{
// 		if (ft_strcmp(env->name, name) == 0)
// 		{
// 			value = ft_strjoin(env->value, value);
// 			env = head;
// 			v_env = update_envl(env, name, value);
// 			shell()->v_env = v_env;
// 			return ;
// 		}
// 		env = env->next;
// 	}
// 	env = head;
// 	v_env = update_envl(env, name, value);
// 	shell()->v_env = v_env;
// }



// void	updt_envl(t_exp_buff *exp_buff, t_env *env, t_env *new)
// {
// 	char	*name;
// 	char	*value;

// 	(void)new;
// 	// t_env	*v_env;
// 	name = exp_buff->name;
// 	value = exp_buff->value;
// 	shell()->v_env = update_envl(env, name, value);
// 	// shell()->v_env = v_env;
// }
