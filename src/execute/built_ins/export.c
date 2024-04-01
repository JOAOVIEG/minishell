/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/01 17:41:34 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

t_exp_buff	*init_exp_data(char **args, char **delimiter)
{
	t_exp_buff	*data;

	data = ft_calloc(1, sizeof(t_exp_buff));
	if (!data)
	{
		perror("Error allocating memory for export data\n");
		exit(EXIT_FAILURE);
	}
	init_exp_buff(data);
	if (!args[1])
	{
		clean_exp_buff(data);
		return (data);
	}
	*delimiter = NULL;
	if (ft_strstr(args[1], "+="))
		*delimiter = "+=";
	else if (ft_strchr(args[1], '='))
		*delimiter = "=";
	return (data);
}

t_exp_buff	*get_exp_data(char **args)
{
	t_exp_buff	*data;
	char		*delimiter;

	data = init_exp_data(args, &delimiter);
	if (!delimiter)
		return (data);
	data->name = ft_strdup(ft_strtok(args[1], delimiter));
	if (args[2])
		data->value = ft_strdup(args[2]);
	else
		data->value = ft_strdup(ft_strtok(NULL, delimiter));
	data->equal = ft_strdup(delimiter);
	return (data);
}

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
