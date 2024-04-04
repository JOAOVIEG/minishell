/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:28:10 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/04 15:23:31 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_env_vars(t_env *current)
{
	int	count;

	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**allocate_envp(int count)
{
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * (count + 1));
	check_new_malloc((t_env *)envp);
	return (envp);
}

char	**env_list_to_arr(void)
{
	int		count;
	int		i;
	t_env	*current;
	char	**envp;
	char	*tmp;

	i = 0;
	current = shell()->v_env;
	count = count_env_vars(current);
	envp = allocate_envp(count);
	while (i < count)
	{
		tmp = ft_strjoin(current->name, "=");
		envp[i] = ft_strjoin(tmp, current->value);
		check_new_malloc((t_env *)envp[i]);
		free(tmp);
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}
