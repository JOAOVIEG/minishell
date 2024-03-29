/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:39:32 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/29 19:01:11 by wiferrei         ###   ########.fr       */
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
