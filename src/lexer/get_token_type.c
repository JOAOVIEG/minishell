/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:12:59 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 19:42:51 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node_type	get_token_type(t_token *token)
{
	if (ft_strcmp(token->value, "|") == 0)
		return (NODE_PIPE);
	else if (ft_strcmp(token->value, "<") == 0)
		return (NODE_REDIRECT_IN);
	else if (ft_strcmp(token->value, ">") == 0)
		return (NODE_REDIRECT_OUT);
	// else if (is_command_path(token->value))
	// {
	// 	return (NODE_CMDPATH);
	// }
	else
	{
		return (NODE_ARGUMENT);
	}
}
