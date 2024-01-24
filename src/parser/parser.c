/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:01:18 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/24 17:55:50 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
	{
		perror("Error allocating memory for parser\n");
		exit(EXIT_FAILURE);
	}
	parser->ast = NULL;
	return (parser);
}


