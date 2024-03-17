/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:53:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/17 20:54:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_invalid_variable(char *name)
{
	int	i;

	if (name == NULL || name[0] == '\0')
		return (1);
	if (ft_isdigit(name[0]))
		return (1);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			if (name[i] != '+' || name[i + 1] != '\0')
				return (1);
		}
		i++;
	}
	i = 0;
	return (0);
}
