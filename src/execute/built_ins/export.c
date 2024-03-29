/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/29 20:14:52 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			env_list->value = ft_strdup(data->value);
			return (head);
		}
		prev = env_list;
		env_list = env_list->next;
	}
	new_env_var = malloc(sizeof(t_env));
	if (!new_env_var)
		return (NULL);
	new_env_var->name = ft_strdup(data->name);
	new_env_var->value = ft_strdup(data->value);
	new_env_var->next = NULL;
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

bool	verify_env_name(t_exp_buff *data)
{
	char	err_msg[256];

	if (is_invalid_variable(data->name))
	{
		data->name = ft_strjoin(data->name, data->equal);
		data->name = ft_strjoin(data->name, data->value);
		sprintf(err_msg, "bash: export: `%s': not a valid identifier\n",
				data->name); // implement my function
		ft_putstr_fd(err_msg, STDERR_FILENO);
		return (false);
	}
	return (true);
}

t_exp_buff	*get_exp_data(char **args)
{
	t_exp_buff	*data;

	data = ft_calloc(1, sizeof(t_exp_buff));
	if (!data)
	{
		perror("Error allocating memory for export data\n");
		exit(EXIT_FAILURE);
	}
	init_exp_buff(data);
	if (args[1] && !args[2])
	{
		if (ft_strstr(args[1], "+="))
		{
			data->name = ft_strdup(ft_strtok(args[1], "+="));
			data->value = ft_strdup(ft_strtok(NULL, "+="));
			data->equal = ft_strdup("+=");
		}
		else if (ft_strchr(args[1], '='))
		{
			data->name = ft_strdup(ft_strtok(args[1], "="));
			data->value = ft_strdup(ft_strtok(NULL, "="));
			data->equal = ft_strdup("=");
		}
	}
	else if (args[1] && args[2])
	{
		if (ft_strstr(args[1], "=_"))
		{
			if (ft_strstr(args[1], "+="))
			{
				data->name = ft_strdup(ft_strtok(args[1], "+=_"));
				data->value = ft_strdup(args[2]);
				data->equal = ft_strdup("+=");
			}
			else if (ft_strchr(args[1], '='))
			{
				data->name = ft_strdup(ft_strtok(args[1], "=_"));
				data->value = ft_strdup(args[2]);
				data->equal = ft_strdup("=");
			}
		}
	}
	else
		clean_exp_buff(data);
	return (data);
}

void	export(char **arg)
{
	t_exp_buff	*exp_data;

	if (!arg[1])
		display_exp_var(shell()->v_env);
	else
	{
		exp_data = get_exp_data(arg);
		if (exp_data && exp_data->equal)
		{
			if (verify_env_name(exp_data))
			{
				if (ft_strcmp(exp_data->equal, "+=") == 0)
					shell()->v_env = concatenate_envl(shell()->v_env, exp_data);
				else if (ft_strcmp(exp_data->equal, "=") == 0)
					shell()->v_env = update_envl(shell()->v_env, exp_data);
			}
			else
			{
				shell()->status = EXIT_FAILURE;
				clean_exp_buff(exp_data);
				return ;
			}
		}
		clean_exp_buff(exp_data);
	}
	shell()->status = EXIT_SUCCESS;
}
