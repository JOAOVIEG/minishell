/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_null.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:08:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/25 15:27:21 by joaocard         ###   ########.fr       */
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
