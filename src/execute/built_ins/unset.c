/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:20:14 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/13 20:23:21 by joaocard         ###   ########.fr       */
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
	if (shell()->status != 0)
		shell()->status = 0;
}

void	update_env_list(char **env)
{
	free_env();
	shell()->v_env = env_cpy(env);
}

// int	is_readonly(char *arg)
// {
// 	According to bash reference, 
// 	"Readonly variables and functions may not be unset".
// 	from my research they are set to readonly with function readonly:
// 	how to flag it here with allowed funcs?
// }



// int	unset_function(char *arg)
// {
// 	According to bash reference:
// 	 if there is no variable by that name, a function with that name, if
// 	any, is unset.
// 	From research function refers to any function defined in the terminal:
// 	function greet() {
//     echo "Hello, $1"
// 	}	is this expansions???
// 	how to unset greet, as example, if nor readonly. This feature is needed?
// }