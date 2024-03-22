/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/22 17:21:12 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = (t_parser *)ft_calloc(1, sizeof(t_parser));
	if (!parser)
	{
		perror("Error allocating memory for parser\n");
		exit(EXIT_FAILURE);
	}
	parser->tokens = NULL;
	parser->q_tokens = NULL;
	parser->pipe_count = 0;
	parser->redir_count = 0;
	parser->heredoc_count = 0;
	return (parser);
}

bool	test_token(t_lst_tokens *tokens)
{
	if (tokens && !tokens->next)
	{
		if (ft_strcmp(tokens->data, "test") == 0)
		{
			shell()->status = 1;
			return (true);
		}
	}
	return (false);
}

void	remove_quotes(t_parser *parser)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = parser->tokens;
	current = head;
	while (current)
	{
		if (current->data[0] == '\'')
			current->data = ft_strtrim(current->data, "\'");
		else if (current->data[0] == '"')
			current->data = ft_strtrim(current->data, "\"");
		current = current->next;
	}
	parser->tokens = head;
}

void	parser(t_shell *shell)
{
	t_lst_tokens	*head;

	tokenize_input(shell->line, shell->lexer);
	parse_to_list(shell->lexer, shell->parser);
	if (test_token(shell->parser->tokens) == true)
		return ;
	head = shell->parser->tokens;
	if (grammar_check(shell->parser) == true)
	{
		make_expansion(shell);
		get_token_type(shell->parser->tokens);
		remove_quotes(shell->parser);
		build_tree(shell);
	}
	else
		shell->parser->tokens = head;
}
