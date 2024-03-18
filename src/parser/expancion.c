/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:49:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/17 21:04:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_var_not_found(t_env_var_replacement *replacement, char *trimmed)
{
	char	*new_data;

	replacement->value = "";
	new_data = create_env_data(replacement);
	free((*(replacement->current))->data);
	(*(replacement->current))->data = new_data;
	free(replacement->substring);
	free(trimmed);
}

void	make_the_replacement(t_env_var_replacement *replacement, char *trimmed)
{
	char	*new_data;

	new_data = create_env_data(replacement);
	free((*(replacement->current))->data);
	(*(replacement->current))->data = new_data;
	if (replacement->substring)
		free(replacement->substring);
	if (replacement->end)
		replacement->end = NULL;
	if (replacement->start)
		replacement->start = NULL;
	if (trimmed)
		free(trimmed);
}

void	replace_with_env_var(t_lst_tokens **current, t_env *env)
{
	t_env_var_replacement	replacement;
	char					*trimmed;
	char					*data_trimmed;

	replacement.current = current;
	init_env_var_replacement(current, &replacement);
	data_trimmed = ft_strtrim(replacement.substring, "$");
	trimmed = ft_strdup(data_trimmed);
	free(data_trimmed);
	if (ft_strncmp(trimmed, "?", 1) == 0)
	{
		replacement.value = ft_itoa(shell()->status);
		make_the_replacement(&replacement, trimmed);
		free(replacement.value);
		return ;
	}
	else if (find_env_value(env, trimmed))
	{
		replacement.value = find_env_value(env, trimmed);
		make_the_replacement(&replacement, trimmed);
		return ;
	}
	env_var_not_found(&replacement, trimmed);
}

void	replace_env_var_in_token(t_lst_tokens **current, t_env *env)
{
	while (ft_strchr((*current)->data, '$'))
		replace_with_env_var(current, env);
}

void	make_expansion(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = shell->parser->tokens;
	current = head;
	while (current)
	{
		if (current->type == TYPE_ENV_VAR)
		{
			if (env_var_quotes(current) != SINGLE_QUOTED
				&& env_var_quotes(current) != DOUBLE_IN_SINGLE_QUOTED)
				replace_env_var_in_token(&current, shell->v_env);
		}
		current = current->next;
	}
}
