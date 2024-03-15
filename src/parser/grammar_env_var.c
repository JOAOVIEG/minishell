/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:32:37 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:56:47 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_env_var_format(char *data)
{
	char	*p;

	if (data[0] != '$' || ft_strlen(data) < 2)
	{
		status_error(data, "Syntax error: malformed environment variable",
			STDERR_FILENO);
		shell()->status = 258;
		return (false);
	}
	p = data + 1;
	while (*p)
	{
		if (!ft_isalnum(*p) && *p != '_')
		{
			status_error(data, "Syntax error: malformed environment variable",
				STDERR_FILENO);
			shell()->status = 258;
			return (false);
		}
		p++;
	}
	return (true);
}

bool	grammar_env_var(t_parser *parser)
{
	if (!parser->tokens)
	{
		status_error("", "Syntax error: unexpected end of input after env var",
			STDERR_FILENO);
		shell()->status = 258;
		return (false);
	}
	if (parser->tokens->type == TYPE_ENV_VAR)
	{
		if (!check_env_var_format(parser->tokens->data))
			return (false);
		parser->tokens = parser->tokens->next;
	}
	return (true);
}
