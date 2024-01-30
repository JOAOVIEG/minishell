/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:07:06 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 12:08:38 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	count_pipes_and_redirections(t_parser *parser, t_token *tokens)
{
	t_token *current;

	current = tokens;
	parser->nbr_pipes = 0;
	parser->nbr_redir_in = 0;
	parser->nbr_redir_out = 0;
	while (current != NULL)
	{
		if ((ft_strcmp(current->value, "|")) == 0)
			parser->nbr_pipes++;
		if ((ft_strcmp(current->value, "<")) == 0)
			parser->nbr_redir_in++;
		if ((ft_strcmp(current->value, ">")) == 0)
			parser->nbr_redir_out++;
		current = current->next;
	}
}