/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:54 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/22 14:01:57 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(char *arg)
{
	t_env	*env;
	t_env	*new;
	char	*equal;
	char	*name;
	char	*value;
	
	env = shell()->v_env;
	if (!arg)
	{
		while (env)
		{
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
			env = env->next;
		}
	}
	else
	{
		equal = strchr(arg, '=');
		if (!equal)
			return ;
		name = malloc((equal - arg) + 1);
		ft_strncpy(name, arg, equal - arg);
		name[equal - arg] = '\0';
		value = ft_strdup(equal + 1);
		while (env && ft_strcmp(env->name, name) != 0)
			env = env->next;
		if (env)
			env->value = ft_strdup(value);
		else
		{
			new = malloc(sizeof(t_env));
			new->name = name;
			new->value = value;
			new->next = shell()->v_env;
			shell()->v_env = new->next;
		}
	}
}
