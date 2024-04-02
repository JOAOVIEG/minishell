/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:20:24 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/02 08:43:08 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	display_exp_var(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

t_env	*new_env_var_node(t_exp_buff *data)
{
	t_env	*new_env_var;

	new_env_var = ft_calloc(1, sizeof(t_env));
	if (!new_env_var)
	{
		perror("Error allocating memory for new environment variable\n");
		exit(EXIT_FAILURE);
	}
	new_env_var->name = ft_strdup(data->name);
	new_env_var->value = ft_strdup(data->value);
	new_env_var->next = NULL;
	return (new_env_var);
}

t_env	*update_envl(t_env *env_list, t_exp_buff *data)
{
	t_env	*head;
	t_env	*prev;
	t_env	*new_env_var;

	head = env_list;
	prev = NULL;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, data->name) == 0)
		{
			free(env_list->value);
			env_list->value = ft_strdup(data->value);
			return (head);
		}
		prev = env_list;
		env_list = env_list->next;
	}
	new_env_var = new_env_var_node(data);
	if (!head)
		head = new_env_var;
	else
		prev->next = new_env_var;
	return (head);
}

t_env	*concatenate_envl(t_env *env_list, t_exp_buff *data)
{
	t_env	*head;
	char	*new_value;

	head = env_list;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, data->name) == 0)
		{
			new_value = ft_strjoin(env_list->value, data->value);
			free(env_list->value);
			env_list->value = new_value;
			return (head);
		}
		env_list = env_list->next;
	}
	return (update_envl(head, data));
}
