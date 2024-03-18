/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:49:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/18 15:47:44 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_n_found(t_env_var_replacement *rplcmnt, char *trimmed)
{
	char	*new_data;

	rplcmnt->value = "";
	new_data = create_env_data(rplcmnt);
	free((*(rplcmnt->current))->data);
	(*(rplcmnt->current))->data = new_data;
	free(rplcmnt->substring);
	free(trimmed);
}

void	make_rplcmnt(t_env_var_replacement *rplcmnt, char *trimmed)
{
	char	*new_data;

	new_data = create_env_data(rplcmnt);
	free((*(rplcmnt->current))->data);
	(*(rplcmnt->current))->data = new_data;
	if (rplcmnt->substring)
		free(rplcmnt->substring);
	if (rplcmnt->end)
		rplcmnt->end = NULL;
	if (rplcmnt->start)
		rplcmnt->start = NULL;
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
		make_rplcmnt(&replacement, trimmed);
		free(replacement.value);
		return ;
	}
	else if (find_env_value(env, trimmed))
	{
		replacement.value = find_env_value(env, trimmed);
		make_rplcmnt(&replacement, trimmed);
		return ;
	}
	env_n_found(&replacement, trimmed);
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
