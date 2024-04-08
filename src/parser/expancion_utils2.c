/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 09:54:59 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/08 16:05:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	dollar_sign_isolated(char *str, int index)
{
	int	len;

	len = strlen(str);
	if (index == 0 && !ft_isalnum(str[index + 1]) && str[index + 1] != '?')
		return (true);
	if ((index == len - 1 && !ft_isalnum(str[index - 1])) || (index == len - 1
			&& ft_isalnum(str[index - 1])))
		return (true);
	if (index > 0 && index < len - 1 && !ft_isalnum(str[index - 1])
		&& !ft_isalnum(str[index + 1]))
		return (true);
	return (false);
}

char	*env_n_found(t_env_var_replacement *rplcmnt, char *data)
{
	char	*new_data;

	rplcmnt->value = "";
	new_data = create_env_data(rplcmnt, data);
	return (new_data);
}
