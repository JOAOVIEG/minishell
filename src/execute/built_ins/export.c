/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/27 16:24:20 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*update_envl(t_env *env_list, char *name, char *value)
{
	t_env	*head;
	t_env	*prev;
	t_env	*new_env_var;

	head = env_list;
	prev = NULL;
	while (env_list)
	{
		if (strcmp(env_list->name, name) == 0)
		{
			env_list->value = ft_strdup(value);
			return (head);
		}
		prev = env_list;
		env_list = env_list->next;
	}
	new_env_var = malloc(sizeof(t_env));
	if (!new_env_var)
		return (NULL);
	new_env_var->name = ft_strdup(name);
	new_env_var->value = ft_strdup(value);
	new_env_var->next = NULL;
	if (!head)
		head = new_env_var;
	else
		prev->next = new_env_var;
	return (head);
}

t_env	*concatenate_envl(t_env *env_list, char *name, char *value)
{
	t_env	*head;
	char	*new_value;

	head = env_list;
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
		{
			// is not joining the value correctly
			new_value = ft_strjoin(env_list->value, value);
			free(env_list->value);
			env_list->value = new_value;
			return (head);
		}
		env_list = env_list->next;
	}
	return (update_envl(head, name, value));
}

void	export(char **arg)
{
	char	*name;
	char	*value;
	char	err_msg[256];

	if (!arg[1])
	{
		display_exp_var(shell()->v_env);
		shell()->status = EXIT_SUCCESS;
		return ;
	}
	if (arg[1] && !arg[2])
	{
		if (ft_strstr(arg[1], "+="))
		{
			name = ft_strtok(arg[1], "+=");
			value = ft_strtok(NULL, "+=");
			shell()->v_env = concatenate_envl(shell()->v_env, name, value);
		}
		else if (ft_strchr(arg[1], '='))
		{
			name = ft_strtok(arg[1], "=");
			value = ft_strtok(NULL, "=");
			if (is_invalid_variable(name))
			{
				name = ft_strjoin(name, "=");
				name = ft_strjoin(name, value);
				sprintf(err_msg, "bash: export: `%s': not a valid identifier\n",
						name); // implement my function
				ft_putstr_fd(err_msg, STDERR_FILENO);
				shell()->status = 1;
				return ;
			}
			else
				shell()->v_env = update_envl(shell()->v_env, name, value);
		}
	}
	shell()->status = EXIT_SUCCESS;
}
