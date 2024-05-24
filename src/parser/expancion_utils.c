/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:56:18 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/06 19:50:37 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_quote_type	env_var_quotes(t_lst_tokens *current)
{
	char			*data;
	size_t			len;
	t_quote_type	quote;

	if (!current || !current->data)
		return (NO_QUOTED);
	data = current->data;
	len = ft_strlen(data);
	if (data[0] == '\'' && data[len - 1] == '\'')
	{
		quote = SINGLE_QUOTED;
		if (ft_strchr(data, '"'))
			quote = DOUBLE_IN_SINGLE_QUOTED;
	}
	else if (data[0] == '"' && data[len - 1] == '"')
	{
		quote = DOUBLE_QUOTED;
		if (ft_strchr(data, '\''))
			quote = SINGLE_IN_DOUBLE_QUOTED;
	}
	else
		quote = NO_QUOTED;
	return (quote);
}

char	*find_end_of_env_var(const char *str)
{
	const char	*s;

	s = str;
	if (*s == '$')
		s++;
	if (*s == '?')
		return ((char *)(s + 1));
	if (!(*s == '_' || (*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')))
		return (NULL);
	s++;
	while (*s == '_' || (*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')
		|| (*s >= '0' && *s <= '9'))
		s++;
	return ((char *)s);
}

char	*create_env_data(t_env_var_replacement *replacement, char *data)
{
	char	*new_data;

	new_data = ft_calloc(ft_strlen(data) - ft_strlen(replacement->substring)
			+ ft_strlen(replacement->value) + 1, sizeof(char));
	ft_strncpy(new_data, data, replacement->start - data);
	ft_strcat(new_data, replacement->value);
	ft_strncat(new_data, replacement->end, data + ft_strlen(data)
		- replacement->end);
	return (new_data);
}

void	init_env_var_replacement(char *data, t_env_var_replacement *replacement)
{
	replacement->start = ft_strchr(data, '$');
	replacement->end = find_end_of_env_var(replacement->start);
	if (!replacement->end)
		replacement->end = replacement->start + ft_strlen(replacement->start);
	replacement->substring = ft_strndup(replacement->start, replacement->end
			- replacement->start);
}

char	*find_env_value(t_env *env, char *trimmed)
{
	t_env	*current_env;

	current_env = env;
	while (current_env)
	{
		if (ft_strncmp(trimmed, current_env->name,
				ft_strlen(current_env->name)) == 0)
			return (current_env->value);
		current_env = current_env->next;
	}
	return (NULL);
}
