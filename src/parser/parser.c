/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:18:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/06 18:08:25 by wiferrei         ###   ########.fr       */
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

void	remove_quotes_env(t_parser *parser)
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

void	replace_with_env_var(t_lst_tokens **current, t_env *env)
{
    char	*start;
    char	*end;
    char	*substring;
    char	*trimmed;
    char	*value;
    t_env	*current_env;
    char	*new_data;

    current_env = env;
    start = ft_strchr((*current)->data, '$');
    end = strpbrk(start, " \t\n\0"); /* define my own function */
    if (!end)
        end = start + ft_strlen(start);
    substring = ft_strndup(start, end - start);
    trimmed = ft_strdup(ft_strtrim(substring, "$"));
    while (current_env)
    {
        if (ft_strncmp(trimmed, current_env->name,
                ft_strlen(current_env->name)) == 0)
        {
            value = ft_strdup(current_env->value);
            new_data = malloc(ft_strlen((*current)->data) - ft_strlen(substring) + ft_strlen(value) + 1);
            strncpy(new_data, (*current)->data, start - (*current)->data);  // Copy the part before the substring
            new_data[start - (*current)->data] = '\0';  // Null-terminate the new string
            strcat(new_data, value);  // Append the replacement text
            strncat(new_data, end, (*current)->data + ft_strlen((*current)->data) - end);  // Append the part after the substring
            free((*current)->data);
            (*current)->data = new_data;
        }
        current_env = current_env->next;
    }
    free(substring);
    free(trimmed);
}

void	make_env_var(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;
	t_env			*env;
	t_env			*current_env;
	char			*value;
	char			*trimmed;

	// char			*start;
	// char			*end;
	// char			*substring;
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
			current->data = ft_strdup(trimmed);
			free(trimmed);
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
			current_env = env;
		}
		if (current->type == TYPE_ARG || current->type == TYPE_COMMAND)
		{
			if (ft_strchr(current->data, '$'))
			{
				// start = ft_strchr(current->data, '$');
				// end = strpbrk(start, " \t\n\0"); /* define my own function */
				// if (!end)
				// 	end = start + ft_strlen(start);
				// substring = ft_strndup(start, end - start);
				// trimmed = ft_strdup(ft_strtrim(substring, "$"));
				// printf("Substring: %s\n", substring);
				// printf("Trimmed: %s\n", trimmed);
				// free(substring);

				replace_with_env_var(&current, current_env);
				printf("ATTENTION: I NEED TO IMPLEMENT THIS CASE\n");
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
	if (grammar_check(shell->parser) == true)
	{
		remove_quotes(shell->parser);
		remove_quotes_env(shell->parser);
		// get_token_type(shell->parser->tokens);
		make_env_var(shell);
		build_tree(shell);
	}
	reset_parser(shell->parser);
	// print_list(shell->parser->tokens);
}
