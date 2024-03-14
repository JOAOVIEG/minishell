/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:59:25 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 19:48:32 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == CHAR_WHITESPACE || c == CHAR_TAB || c == CHAR_NEWLINE)
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == CHAR_SINGLE_QUOTE || c == CHAR_DOUBLE_QUOTE)
		return (1);
	return (0);
}

int	skip_whitespace(char *input, int i)
{
	while (is_whitespace(input[i]))
		i++;
	return (i);
}
