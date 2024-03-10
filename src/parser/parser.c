/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/10 13:23:51 by joaocard         ###   ########.fr       */
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
			if (current->data[0] == '\'')
				current->data = ft_strtrim(current->data, "\'");
			else if (current->data[0] == '"')
				current->data = ft_strtrim(current->data, "\"");
		}
		current = current->next;
	}
	parser->tokens = head;
}

t_quote_type	env_var_quotes(t_lst_tokens *current)
{
	char			*data;
	size_t			len;
	t_quote_type	quote;

	if (!current || !current->data)
		return (NO_QUOTED);
	data = current->data;
	len = ft_strlen(data);
	if (data[0] == '\'' && data[len - 1] == '\'')
	{
		quote = SINGLE_QUOTED;
		if (ft_strchr(data, '"'))
			quote = DOUBLE_IN_SINGLE_QUOTED;
	}
	else if (data[0] == '"' && data[len - 1] == '"')
	{
		quote = DOUBLE_QUOTED;
		if (ft_strchr(data, '\''))
			quote = SINGLE_IN_DOUBLE_QUOTED;
	}
	else
		quote = NO_QUOTED;
	return (quote);
}

void	print_quoted(t_shell shell)
{
	t_lst_tokens	*current;

	current = shell.parser->tokens;
	while (current)
	{
		if (current->type == TYPE_ENV_VAR)
		{
			if (env_var_quotes(current) == SINGLE_QUOTED)
				printf("SINGLE_QUOTED\n");
			else if (env_var_quotes(current) == DOUBLE_QUOTED)
				printf("DOUBLE_QUOTED\n");
			else if (env_var_quotes(current) == SINGLE_IN_DOUBLE_QUOTED)
				printf("SINGLE_IN_DOUBLE_QUOTED\n");
			else if (env_var_quotes(current) == DOUBLE_IN_SINGLE_QUOTED)
				printf("DOUBLE_IN_SINGLE_QUOTED\n");
			else if (env_var_quotes(current) == NO_QUOTED)
				printf("NO_QUOTED\n");
		}
		current = current->next;
	}
}

char	*find_end_of_env_var(const char *str)
{
	const char	*s;

	s = str;
	if (*s == '$')
		s++;
	if (!(*s == '_' || (*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')))
		return (NULL);
	s++;
	while (*s == '_' || (*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')
		|| (*s >= '0' && *s <= '9'))
		s++;
	return ((char *)s);
}

char	*create_env_data(t_env_var_replacement *replacement)
{
	char	*new_data;

	new_data = ft_calloc(ft_strlen((*replacement->current)->data)
			- ft_strlen(replacement->substring) + ft_strlen(replacement->value)
			+ 1, sizeof(char));
	ft_strncpy(new_data, (*replacement->current)->data, replacement->start
		- (*replacement->current)->data);
	ft_strcat(new_data, replacement->value);
	ft_strncat(new_data, replacement->end, (*replacement->current)->data
		+ ft_strlen((*replacement->current)->data) - replacement->end);
	return (new_data);
}

void	init_env_var_replacement(t_lst_tokens **current,
		t_env_var_replacement *replacement)
{
	replacement->current = current;
	replacement->start = ft_strchr((*current)->data, '$');
	replacement->end = find_end_of_env_var(replacement->start);
	if (!replacement->end)
		replacement->end = replacement->start + ft_strlen(replacement->start);
	replacement->substring = ft_strndup(replacement->start, replacement->end
			- replacement->start);
}

void	env_var_not_found(t_env_var_replacement *replacement, char *trimmed)
{
	char	*new_data;

	replacement->value = "";
	new_data = create_env_data(replacement);
	free((*(replacement->current))->data);
	(*(replacement->current))->data = new_data;
	free(replacement->substring);
	free(trimmed);
}

void	replace_with_env_var(t_lst_tokens **current, t_env *env)
{
	t_env_var_replacement	replacement;
	t_env					*current_env;
	char					*trimmed;
	char					*new_data;

	current_env = env;
	replacement.current = current;
	init_env_var_replacement(current, &replacement);
	trimmed = ft_strdup(ft_strtrim(replacement.substring, "$"));
	while (current_env)
	{
		if (ft_strncmp(trimmed, current_env->name,
				ft_strlen(current_env->name)) == 0)
		{
			replacement.value = current_env->value;
			new_data = create_env_data(&replacement);
			free((*(replacement.current))->data);
			(*(replacement.current))->data = new_data;
			free(replacement.substring);
			free(trimmed);
			return ;
		}
		current_env = current_env->next;
	}
	env_var_not_found(&replacement, trimmed);
}

void	replace_env_var_in_token(t_lst_tokens **current, t_env *env)
{
	while (ft_strchr((*current)->data, '$'))
		replace_with_env_var(current, env);
}

void	make_expansion(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = shell->parser->tokens;
	current = head;
	while (current)
	{
		if (current->type == TYPE_ENV_VAR)
		{
			if (env_var_quotes(current) != SINGLE_QUOTED
				&& env_var_quotes(current) != DOUBLE_IN_SINGLE_QUOTED)
				replace_env_var_in_token(&current, shell->v_env);
		}
		current = current->next;
	}
}

void	parser(t_shell *shell)
{
	tokenize_input(shell->line, shell->lexer);
	parse_to_list(shell->lexer, shell->parser);
	if (grammar_check(shell->parser) == true)
	{
		make_expansion(shell);
		get_token_type(shell->parser->tokens);
		remove_quotes(shell->parser);
		build_tree(shell);
	}
	reset_parser(shell->parser);
}
