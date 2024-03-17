/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 20:06:40 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	find_char_index(char *str, char c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (ptr)
		return (ptr - str);
	else
		return (-1);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	init_exp_buff(t_exp_buff *exp_buff)
{
	exp_buff->name = NULL;
	exp_buff->value = NULL;
	exp_buff->equal = NULL;
}

void	clean_exp_buff(t_exp_buff *exp_buff)
{
	if (exp_buff->name)
		free(exp_buff->name);
	if (exp_buff->value)
		free(exp_buff->value);
}

void	handle_equal(char **arg, char **name, char **value, char *equal)
{
	if (equal)
	{
		*name = get_var_name(arg[1], equal);
		*value = ft_strdup(equal + 1);
	}
	else
	{
		*name = ft_strdup(arg[1]);
		*value = get_var_value(shell()->v_env, *name);
	}
}

void	handle_export_var_error(t_exp_buff *exp_buff)
{
	printf("minishell: export: `%s': not a valid identifier\n", exp_buff->name);
	shell()->status = STDERR_FILENO;
	clean_exp_buff(exp_buff);
}

void	export_does_nothing(t_exp_buff *exp_buff)
{
	shell()->status = EXIT_SUCCESS;
	clean_exp_buff(exp_buff);
}

char	*find_quoted_value(char *value)
{
	t_lst_tokens	*head;
	t_lst_tokens	*current;
	char			*unq_data;

	head = q_lst()->token;
	current = head;
	while (current)
	{
		if ((current->type == TYPE_ARG && current->data[0] == '\'')
				|| (current->type == TYPE_ARG && current->data[0] == '"'))
		{
			printf("here\n");
			unq_data = ft_strsub(current->data, 1, ft_strlen(current->data)
					- 2);
			if (ft_strcmp(current->data, value) == 0)
			{
				free(unq_data);
				return (ft_strdup(current->data));
			}
			free(unq_data);
		}
		current = current->next;
	}
	return (ft_strdup(value));
}

void	handle_export_with_args(char **arg, t_exp_buff *exp_buff, t_env **new)
{
	*new = NULL;
	exp_buff->name = ft_strdup(arg[1]);
	if (ft_strchr(exp_buff->name, '='))
	{
		if (exp_buff->name[(find_char_index(exp_buff->name, '=')) + 1] == '\0')
		{
			exp_buff->value = ft_strdup(find_quoted_value(arg[2]));
			if (exp_buff->value[0] == '\'' || exp_buff->value[0] == '"')
			{
				exp_buff->value = ft_strtrim(exp_buff->value, "'");
				exp_buff->value = ft_strtrim(exp_buff->value, "\"");
			}
			else
			{
				free(exp_buff->value);
				exp_buff->value = ft_strdup("");
			}
		}
		else
			exp_buff->value = ft_strdup("");
		exp_buff->name = ft_strtrim(exp_buff->name, "_");
		exp_buff->name = ft_strtrim(exp_buff->name, "=");
	}
}

int	choose_export_action(t_exp_buff *exp_buff, t_env *env, t_env *new)
{
	if (exp_buff->name[0] == '_' && exp_buff->name[1] == '\0')
	{
		export_does_nothing(exp_buff);
		return (1);
	}
	if (is_invalid_variable(exp_buff->name))
	{
		handle_export_var_error(exp_buff);
		return (1);
	}
	if (ft_strchr(exp_buff->name, '+'))
	{
		exp_buff->name = ft_strtrim(exp_buff->name, "+");
		concatonate_and_update(env, new, exp_buff->name, exp_buff->value);
	}
	else
		shell()->v_env = update_envl(env, new, exp_buff->name, exp_buff->value);
	return (0);
}

void	export(char **arg)
{
	t_env		*env;
	t_env		*new;
	t_exp_buff	exp_buff;

	init_exp_buff(&exp_buff);
	env = shell()->v_env;
	if (!arg[1])
		display_exp_var(env);
	else if (arg[1] && !arg[2])
	{
		new = NULL;
		exp_buff.equal = get_equal(arg[1]);
		handle_equal(arg, &exp_buff.name, &exp_buff.value, exp_buff.equal);
	}
	else
		handle_export_with_args(arg, &exp_buff, &new);
	if (choose_export_action(&exp_buff, env, new))
		return ;
	shell()->status = EXIT_SUCCESS;
}

t_env	*create_var(t_env *new, char *name, char *value)
{
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = shell()->v_env;
	shell()->v_env = new;
	return (new);
}

char	*get_var_name(char *arg, char *equal)
{
	char	*name;
	int		length;

	length = 0;
	while (&arg[length] != equal)
		length++;
	name = malloc(sizeof(char) * (length + 1));
	ft_strncpy(name, arg, length);
	name[length] = '\0';
	return (name);
}

void	concatonate_and_update(t_env *env, t_env *new, char *name, char *value)
{
	t_env	*head;

	head = env;
	while (env->next != NULL)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			value = ft_strjoin(env->value, value);
			env = head;
			shell()->v_env = update_envl(env, new, name, value);
			return ;
		}
		env = env->next;
	}
	env = head;
	shell()->v_env = update_envl(env, new, name, value);
}

t_env	*update_envl(t_env *env, t_env *new, char *name, char *value)
{
	t_env	*head;

	head = env;
	while (env && ft_strcmp(env->name, name) != 0)
		env = env->next;
	if (env)
		env->value = ft_strdup(value);
	else if (value)
	{
		new = create_var(new, name, value);
		new->next = head;
		head = new;
	}
	return (head);
}

char	*get_equal(char *arg)
{
	char	*equal;

	equal = ft_strchr(arg, '=');
	return (equal);
}

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
