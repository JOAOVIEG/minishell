/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:20:14 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/10 13:00:13 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	unset(char **arg)
{
	char	**env;
	int		i;
	int 	j;
	
	i = 1;
	env = env_list_to_arr();
	while (arg[i])
	{
		j = 0;
		while (env[j])
		{
			if(ft_strnstr(env[j], arg[i], (ft_strchr(env[j], '=') - env[j])) != NULL)
			{
				free(env[j]);
				backshift(env, j);
			}
			else
				j++;
		}
		i++;
	}
	update_env_list(env);
	free_c_env(env);
	return (shell()->status);
}

void	backshift(char **env, int start)
{
	int k;

	k = start;
	while (env[k])
	{
		env[k] = env[k + 1];
		k++;
	}
	free(env[k]);
	if (shell()->status != EXIT_SUCCESS)
		shell()->status = EXIT_SUCCESS;
}

void	update_env_list(char **env)
{
	free_env();
	shell()->v_env = env_cpy(env);
}
