/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_get_next_precedence.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:03:35 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 10:09:21 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ast_get_next_precedence(t_token_type op)
{
	if (op == NODE_PIPE)
		return (1);
	else if (op == NODE_REDIRECT_IN || op == NODE_REDIRECT_OUT)
		return (2);
	else if (op == NODE_CMDPATH)
		return (3);
	else if (op == NODE_ARGUMENT)
		return (4);
	else if (op == NODE_DATA)
		return (5);
	else
		return (-1);
}
