/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_hd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:03:18 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/17 21:04:58 by wiferrei         ###   ########.fr       */
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

	token = malloc(sizeof(t_lst_tokens));
	token->data = *buffer;
	token->type = TYPE_HEREDOC;
	token->next = NULL;
	if (has_env_var(*buffer))
	{
		replace_env_var_in_token(&token, shell()->v_env);
		*buffer = token->data;
	}
	free(token);
}
