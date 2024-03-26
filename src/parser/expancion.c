/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:49:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/26 17:48:42 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	dollar_sign_isolated(char *str, int index)
{
	int	len;

	len = strlen(str);
	if (index == 0 && is_whitespace(str[index + 1]))
		return (true);
	if (index == len - 1 && is_whitespace(str[index - 1]))
		return (true);
	if (index > 0 && index < len - 1 && is_whitespace(str[index - 1])
		&& is_whitespace(str[index + 1]))
		return (true);
	return (false);
}

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

	handle_lonely_dollar(current);
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
	shell->parser->tokens = head;
}
