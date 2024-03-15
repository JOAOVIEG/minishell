/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/15 20:08:47 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export(char **arg)
{
	t_env	*env;
	t_env	*new;
	char	*name;
	char	*value;
	char	*equal;
	int		i;

	i = 1;
	env = shell()->v_env;
	if (!arg[i])
		display_exp_var(env);
	else
	{
		while (arg[i])
		{
			new = NULL;
			equal = get_equal(arg[i]);
			if (equal)
			{
				name = get_var_name(arg[i], equal);
				value = ft_strdup(equal + 1);
			}
			else
			{
				name = ft_strdup(arg[i]);
				value = get_var_value(env, name);
			}
			if (is_invalid_variable(name))
			{
				printf("minishell: export: `%s': not a valid identifier\n",
					name);
				shell()->status = STDERR_FILENO;
				free(name);
				free(value);
				return ;
			}
			shell()->v_env = update_envl(env, new, name, value);
			i++;
		}
	}
	shell()->status = EXIT_SUCCESS;
}

t_env	*create_var(t_env *new, char *name, char *value)
{
	new->name = name;
	new->value = value;
	new->next = shell()->v_env;
	shell()->v_env = new->next;
	return (new);
}

char	*get_var_name(char *arg, char *equal)
{
	char	*name;

	name = malloc(sizeof(char) * ((equal - arg) + 1));
	ft_strncpy(name, arg, equal - arg);
	name[equal - arg] = '\0';
	return (name);
}

t_env	*update_envl(t_env *env, t_env *new, char *name, char *value)
{
	while (env && ft_strcmp(env->name, name) != 0)
		env = env->next;
	if (env)
		env->value = ft_strdup(value);
	else if (!value)
		create_var(new, name, value);
	return (env);
}

char	*get_equal(char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	return (equal);
}

int	is_invalid_variable(char *name)
{
	char	*reserved_keywords[] = {"for", "do", "done", "in", "case", "esac",
			"while", "until", "if", "then", "else", "elif", "fi", "function",
			"time", "{", "}", "!", "[[", "]]", "coproc", "select", NULL};
	int		i;

	if (name == NULL || name[0] == '\0')
		return (1);
	if (ft_isdigit(name[0]))
		return (1);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	i = 0;
	while (reserved_keywords[i] != NULL)
	{
		if (ft_strcmp(name, reserved_keywords[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
