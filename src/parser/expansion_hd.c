/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:03:18 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/08 16:04:59 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	has_env_var(char *str)
{
	if (ft_strchr(str, '$'))
		return (true);
	return (false);
}

void	make_expansion_hd(char **buffer)
{
	t_lst_tokens	*token;
	char			*rep_data;

	token = malloc(sizeof(t_lst_tokens));
	token->data = *buffer;
	token->type = TYPE_HEREDOC;
	token->next = NULL;
	if (has_env_var(*buffer))
	{
		rep_data = get_replaceded_data(&token);
		free(token->data);
		token->data = rep_data;
		*buffer = token->data;
	}
	free(token);
}
