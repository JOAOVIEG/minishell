/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:22:19 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/27 10:55:05 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_current(t_lst_tokens *current, t_shell *shell)
{
	char	*new_data;

	if (current->type == TYPE_ENV_VAR && ft_strchr(current->data, '~'))
	{
		if (ft_strcmp(current->data, "~") == 0)
		{
			free(current->data);
			current->data = ft_strdup("$HOME");
		}
		else if (ft_strstr(current->data, "~/"))
		{
			new_data = ft_search_and_replace_all(current->data, "~",
					find_env_value(shell->v_env, "HOME"));
			free(current->data);
			current->data = new_data;
		}
	}
}

void	handle_tilde(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = shell->parser->tokens;
	current = head;
	while (current)
	{
		process_current(current, shell);
		current = current->next;
	}
	shell->parser->tokens = head;
}
