/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:58:59 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 15:26:43 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)calloc(sizeof(t_token), 1);
	if (!token)
	{
		perror("Error allocating memory for tokens\n");
		exit(EXIT_FAILURE);
	}
	token_init(token);
	return (token);
}
