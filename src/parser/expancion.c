/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expancion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:49:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/02 09:58:17 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
