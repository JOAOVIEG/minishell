/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/03 18:41:41 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*init_parser(void)
{
	t_parser *parser;

	parser = (t_parser *)ft_calloc(1, sizeof(t_parser));
	if (!parser)
	{
		perror("Error allocating memory for parser\n");
		exit(EXIT_FAILURE);
	}
	parser->tokens = NULL;
	return (parser);
}