/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/06 13:35:23 by wiferrei         ###   ########.fr       */
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
	parser->pipe_count = 0;
	parser->redir_count = 0;
	parser->heredoc_count = 0;
	return (parser);
}

void	print_env_list(t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		printf("Name: %s, Value: %s\n", current->name, current->value);
		current = current->next;
	}
}

void	remove_quotes(t_parser *parser)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = parser->tokens;
	current = head;
	while (current)
	{
		if (current->type == TYPE_ARG || current->type == TYPE_COMMAND)
		{
			if (current->data[0] == '\'' || current->data[0] == '\"')
				current->data = ft_strtrim(current->data, "\'\"");
		}
		current = current->next;
	}
	parser->tokens = head;
}

void remove_quotes_env(t_parser *parser)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = parser->tokens;
	current = head;
	while (current)
	{
		if (current->type == TYPE_ENV_VAR)
		{
			if (current->data[0] == '\"')
				current->data = ft_strtrim(current->data, "\'\"");
		}
		current = current->next;
	}
	parser->tokens = head;
}
void	make_env_var(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;
	t_env			*env;
	t_env			*current_env;
	char			*value;
	char			*trimmed;

	head = shell->parser->tokens;
	current = head;
	env = shell->v_env;
	current_env = env;
	while (current)
	{
		if (current->type == TYPE_ENV_VAR)
		{
			trimmed = ft_strtrim(current->data, "$");
			free(current->data);
			current->data = NULL;
			current->data = trimmed;
			while (current_env)
			{
				if (ft_strncmp(current->data, current_env->name,
						ft_strlen(current_env->name)) == 0)
				{
					value = ft_strdup(current_env->value);
					free(current->data);
					current->data = value;
				}
				current_env = current_env->next;
			}
		}
		current = current->next;
	}
	shell->parser->tokens = head;
}

void	parser(t_shell *shell)
{
	tokenize_input(shell->line, shell->lexer);
	parse_to_list(shell->lexer, shell->parser);
	if (grammar_check(shell->parser))
	{
		remove_quotes(shell->parser);
		remove_quotes_env(shell->parser);
		//get_token_type(shell->parser->tokens);
		make_env_var(shell);
		build_tree(shell);
	}
	reset_parser(shell->parser);
	//print_list(shell->parser->tokens);
}
