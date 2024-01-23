/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:20:24 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/23 17:00:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

char	*get_var_value(t_env *env, char *name)
{
	t_env	*check_var;
	char	*value;

	check_var = find_env_var(env, name);
	if (check_var)
		value = ft_strdup(check_var->value);
	else
		value = NULL;
	return (value);
}

void	display_exp_var(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}
