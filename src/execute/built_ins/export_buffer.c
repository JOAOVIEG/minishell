/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:39:32 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/03 15:23:57 by wiferrei         ###   ########.fr       */
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
	if (exp_buff->equal)
	{
		free(exp_buff->equal);
		exp_buff->equal = NULL;
	}
	free(exp_buff);
	exp_buff = NULL;
}

t_exp_buff	*get_exp_data(char *arg)
{
	t_exp_buff	*data;

	data = ft_calloc(1, sizeof(t_exp_buff));
	if (!data)
	{
		perror("Error allocating memory for export data\n");
		exit(EXIT_FAILURE);
	}
	init_exp_buff(data);
	if (ft_strstr(arg, "+="))
	{
		data->name = ft_strtok(arg, "+=");
		data->value = ft_strtok(NULL, "+=");
		data->equal = ft_strdup("+=");
	}
	else if (ft_strchr(arg, '='))
	{
		data->name = ft_strtok(arg, "=");
		data->value = ft_strtok(NULL, "=");
		data->equal = ft_strdup("=");
	}
	else
	{
		data->name = arg;
		data->value = NULL;
		data->equal = NULL;
	}
	return (data);
}