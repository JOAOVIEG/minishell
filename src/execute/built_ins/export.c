/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:26:20 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 20:55:35 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
