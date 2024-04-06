/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:49:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/06 20:01:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*process_replaceded_data(char *data)
// {
// 	char					*rep_data;
// 	t_env_var_replacement	replacement;
// 	char					*trimmed;

// 	init_env_var_replacement(data, &replacement);
// 	trimmed = ft_strtrim(replacement.substring, "$");
// 	if (ft_strncmp(trimmed, "?", 1) == 0)
// 	{
// 		replacement.value = ft_itoa(shell()->status);
// 		rep_data = create_env_data(&replacement, data);
// 		if (replacement.substring)
// 			free(replacement.substring);
// 		if (replacement.value)
// 			free(replacement.value);
// 		if (replacement.end)
// 			replacement.end = NULL;
// 		if (replacement.start)
// 			replacement.start = NULL;
// 		if (trimmed)
// 			free(trimmed);
// 		return (rep_data);
// 	}
// 	else if (find_env_value(shell()->v_env, trimmed))
// 	{
// 		replacement.value = find_env_value(shell()->v_env, trimmed);
// 		rep_data = create_env_data(&replacement, data);
// 		if (replacement.substring)
// 			free(replacement.substring);
// 		if (replacement.end)
// 			replacement.end = NULL;
// 		if (replacement.start)
// 			replacement.start = NULL;
// 		if (trimmed)
// 			free(trimmed);
// 		return (rep_data);
// 	}
// 	rep_data = env_n_found(&replacement, data);
// 	if (replacement.substring)
// 		free(replacement.substring);
// 	if (replacement.end)
// 		replacement.end = NULL;
// 	if (replacement.start)
// 		replacement.start = NULL;
// 	if (trimmed)
// 		free(trimmed);
// 	return (rep_data);
// }

void	clean_env_replacement(t_env_var_replacement *rep, char *trimmed)
{
	if (trimmed)
		free(trimmed);
	if (rep->substring)
		free(rep->substring);
	if (rep->end)
		rep->end = NULL;
	if (rep->start)
		rep->start= NULL;
}

char	*process_replaceded_data(char *data)
{
	char					*rep_data;
	t_env_var_replacement	replacement;
	char					*trimmed;

	init_env_var_replacement(data, &replacement);
	trimmed = ft_strtrim(replacement.substring, "$");
	if (ft_strncmp(trimmed, "?", 1) == 0)
	{
		replacement.value = ft_itoa(shell()->status);
		rep_data = create_env_data(&replacement, data);
		if (replacement.value)
			free(replacement.value);
	}
	else if (find_env_value(shell()->v_env, trimmed))
	{
		replacement.value = find_env_value(shell()->v_env, trimmed);
		rep_data = create_env_data(&replacement, data);
	}
	else
		rep_data = env_n_found(&replacement, data);
	clean_env_replacement(&replacement, trimmed);
	return (rep_data);
}

char	*get_replaceded_data(t_lst_tokens **current)
{
	char	*data;
	char	*tmp;

	data = ft_strdup((*current)->data);
	while (ft_strchr(data, '$'))
	{
		if (dollar_sign_isolated(data, find_char_index(data, '$'))
			&& !(*current)->next)
			data = ft_search_and_replace_first((*current)->data, "$",
					"OnlyDollar");
		else
		{
			tmp = data;
			data = process_replaceded_data(tmp);
			free(tmp);
		}
	}
	if (ft_strstr(data, "OnlyDollar"))
		data = ft_search_and_replace_all(data, "OnlyDollar", "$");
	return (data);
}

void	make_expansion(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;
	char			*rep_data;

	head = shell->parser->tokens;
	current = head;
	while (current)
	{
		if (current->type == TYPE_ENV_VAR)
		{
			if (env_var_quotes(current) != SINGLE_QUOTED
				&& env_var_quotes(current) != DOUBLE_IN_SINGLE_QUOTED)
			{
				rep_data = get_replaceded_data(&current);
				free(current->data);
				current->data = rep_data;
			}
		}
		current = current->next;
	}
	shell->parser->tokens = head;
}
