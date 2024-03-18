/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:20:24 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 20:52:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

char	*get_var_name(char *arg, char *equal)
{
	char	*name;
	int		length;

	length = 0;
	while (&arg[length] != equal)
		length++;
	name = malloc(sizeof(char) * (length + 1));
	ft_strncpy(name, arg, length);
	name[length] = '\0';
	return (name);
}

char	*get_equal(char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	return (equal);
}
