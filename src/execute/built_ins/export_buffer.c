/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:39:32 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/02 09:51:37 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_exp_buff(t_exp_buff *exp_buff)
{
	exp_buff->name = NULL;
	exp_buff->value = NULL;
	exp_buff->equal = NULL;
}

void	clean_exp_buff(t_exp_buff *exp_buff)
{
	if (exp_buff->name)
	{
		free(exp_buff->name);
		exp_buff->name = NULL;
	}
	if (exp_buff->value)
	{
		free(exp_buff->value);
		exp_buff->value = NULL;
	}
	if (exp_buff->equal)
	{
		free(exp_buff->equal);
		exp_buff->equal = NULL;
	}
	free(exp_buff);
	exp_buff = NULL;
}

void	handle_general_case(t_exp_buff *data, char **args)
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

void	hanle_special_case(t_exp_buff *data, char **args)
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
		handle_general_case(data, args);
	else if (args[1] && args[2])
		hanle_special_case(data, args);
	else
		clean_exp_buff(data);
	return (data);
}
