/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:17:40 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/29 19:12:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_is_only_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}

void	remove_token(t_lst_tokens **current, t_lst_tokens **prev,
		t_lst_tokens **next, t_parser *parser)
{
	*next = (*current)->next;
	if (*prev)
		(*prev)->next = *next;
	else
		parser->tokens = *next;
	free((*current)->data);
	free(*current);
}

void	remove_empty_tokens(t_parser *parser)
{
	t_lst_tokens	*current;
	t_lst_tokens	*prev;
	t_lst_tokens	*next;

	current = parser->tokens;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (str_is_only_whitespace(current->data)
			|| only_empty_quotes(current->data))
			remove_token(&current, &prev, &next, parser);
		else
			prev = current;
		current = next;
	}
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
	char			*old_data;

	head = parser->tokens;
	current = head;
	while (current)
	{
		if (current->data[0] == '\'')
		{
			old_data = current->data;
			current->data = ft_strtrim(current->data, "\'");
			free(old_data);
		}
		else if (current->data[0] == '"')
		{
			old_data = current->data;
			current->data = ft_strtrim(current->data, "\"");
			free(old_data);
		}
		current = current->next;
	}
	parser->tokens = head;
}
