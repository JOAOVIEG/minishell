/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:32:48 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/19 17:49:04 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_type(t_lst_tokens *current, t_lst_tokens *prev)
{
	if (ft_strncmp(current->data, "|", 2) == 0)
		current->type = TYPE_PIPE;
	else if (ft_strncmp(current->data, ">", 2) == 0 || ft_strncmp(current->data,
			"<", 2) == 0)
		current->type = TYPE_REDIRECT;
	else if (ft_strncmp(current->data, ">>", 3) == 0)
		current->type = TYPE_REDIRECT;
	else if (ft_strncmp(current->data, "<<", 3) == 0)
		current->type = TYPE_HEREDOC;
	else if (ft_strncmp(current->data, "'", 2) == 0)
		current->type = TYPE_QUOTES;
	else if (ft_strncmp(current->data, "\"", 2) == 0)
		current->type = TYPE_QUOTES;
	else if (ft_strncmp(current->data, "$", 2) == 0)
		current->type = TYPE_ENV_VAR;
	else if (prev == NULL || ft_strncmp(prev->data, "|", 2) == 0
		|| ft_strncmp(prev->data, ";", 2) == 0 || ft_strncmp(prev->data, "&&",
			3) == 0 || ft_strncmp(prev->data, "||", 3) == 0)
		current->type = TYPE_COMMAND;
	else
		current->type = TYPE_ARG;
}

void	get_token_type(t_lst_tokens *tokens)
{
	t_lst_tokens	*current;
	t_lst_tokens	*prev;

	prev = NULL;
	current = tokens;
	while (current != NULL)
	{
		define_type(current, prev);
		prev = current;
		current = current->next;
	}
}
