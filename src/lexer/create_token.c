/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:17:31 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/09 17:58:17 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_token(char *input, int start, int end)
{
	int		token_length;
	char	*token;

	token_length = end - start;
	token = ft_calloc(token_length + 1, sizeof(char));
	ft_memcpy(token, &input[start], token_length);
	token[token_length] = '\0';
	return (token);
}
