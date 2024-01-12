/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:24:18 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/12 18:26:30 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_prompt	*set_prompt(char *str)
{
	t_prompt	*p;

	p = (t_prompt *)malloc(sizeof(t_prompt));
	if (!p)
	{
		printf("Error, malloc failed at prompt.c\n");
		exit(EXIT_FAILURE);
	}
	p->prompt_name = ft_strdup(str);
	return (p);
}
