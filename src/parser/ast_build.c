/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:45:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 14:16:54 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ast_handle_pipes(t_token *tokens, t_parser *parser)
{
	char	*delimiter;

	delimiter = "|";
	parser->buffer = malloc(sizeof(t_parser_buffer));
	if (parser->nbr_pipes == 1)
		split_token_list(tokens, parser, delimiter);
}

void	build_ast(t_token *tokens, t_parser *parser)
{
	// t_astree *root;
	count_pipes_and_redirections(parser, tokens);
	printf("nbr pipes: %d\n", parser->nbr_pipes);
	if (parser->nbr_pipes > 0)
	{
		ast_handle_pipes(tokens, parser);
	}
}
