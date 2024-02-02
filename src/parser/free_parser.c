/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:20:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/02 16:51:39 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_parser(t_parser *parser)
{
	if (parser->tokens)
		printf("Need to free tokens list\n");
	free(parser->tokens);
	free(parser);
}