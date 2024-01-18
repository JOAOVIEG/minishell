/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:26:38 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/18 14:02:25 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*add_env_var(t_env *env, char *name, char *value)
{
	t_env	*new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		perror("malloc failed");
		return (EXIT_FAILURE);
	}
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = env;
	return (new_node);	
}

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*env_cpy(char **envp)
{
	t_env	*env;
	char	*equal_pos;
	char	*name;
	char	*value;
	int		i;

	env = NULL;
	equal_pos = NULL;
	name = NULL;
	value = NULL;
	i = 0;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (equal_pos)
		{
			name = ft_strndup(envp[i], (equal_pos - envp[i]));
			value = ft_strdup(equal_pos + 1);
			env = add_env_var(env, name, value);
			free(name);
			free(value);
		}
	}
return (env);
}
