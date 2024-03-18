/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:26:38 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/18 08:14:03 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*find_env_var(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	get_var(t_env *new, char *envp, char *equal_pos)
{
	new->name = ft_strndup(envp, (equal_pos - envp));
	new->value = ft_strdup(equal_pos + 1);
	new->next = NULL;
}

void	new_var(t_env **head, t_env *tail, t_env *new)
{
	if (tail)
		tail->next = new;
	else
		*head = new;
}

void	check_new_malloc(t_env *new)
{
	if (!new)
	{
		printf("minishell: %s\n", strerror(errno));
		exit(shell()->status);
	}
}

t_env	*env_cpy(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;
	char	*equal_pos;

	head = NULL;
	tail = NULL;
	while (*envp)
	{
		if (*envp != NULL)
		{
			new = malloc(sizeof(t_env));
			check_new_malloc(new);
			equal_pos = ft_strchr(*envp, '=');
			if (equal_pos)
			{
				get_var(new, *envp, equal_pos);
				new_var(&head, tail, new);
				tail = new;
			}
			else
				free(new);
		}
		envp++;
	}
	return (head);
}

char	**env_list_to_arr(void)
{
	int		count;
	int		i;
	t_env	*current;
	char	**envp;
	char	*tmp;

	count = 0;
	i = 0;
	current = shell()->v_env;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		perror("malloc envp");
		exit(EXIT_FAILURE);
	}
	current = shell()->v_env;
	while (i < count)
	{
		tmp = ft_strjoin(current->name, "=");
		envp[i] = ft_strjoin(tmp, current->value);
		if (!envp[i])
		{
			perror("malloc envp[i]");
			free_c_env(envp);
			exit(EXIT_FAILURE);
		}
		free(tmp);
		i++;
		current = current->next;
	}
	tmp = NULL;
	envp[i] = NULL;
	return (envp);
}
