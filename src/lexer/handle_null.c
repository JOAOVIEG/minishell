/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:08:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 15:16:49 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*handle_null(t_token *token, t_lexer *lexer, t_tk_buffer *buffer)
{
	if (buffer->j > 0)
	{
		token->value[buffer->j] = 0;
		lexer->ntoks++;
		buffer->j = 0;
	}
	return (token);
}