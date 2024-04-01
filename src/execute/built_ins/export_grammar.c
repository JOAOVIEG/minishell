/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:53:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/01 17:21:04 by wiferrei         ###   ########.fr       */
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

bool	verify_env_name(t_exp_buff *data)
{
	char	*err_msg;

	if (is_invalid_variable(data->name))
	{
		data->name = ft_strjoin(data->name, data->equal);
		data->name = ft_strjoin(data->name, data->value);
		err_msg = ft_strdup("bash: export: `%s': not a valid identifier\n");
		if (!err_msg)
		{
			perror("Error allocating memory for error message\n");
			exit(EXIT_FAILURE);
		}
		err_msg = ft_search_and_replace_all(err_msg, "%s", data->name);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		free(err_msg);
		return (false);
	}
	return (true);
}
