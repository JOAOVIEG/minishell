/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/31 13:55:19 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"
# include "../../includes/lexer.h"
# include "../../includes/parser.h"

void	ft_execute(void)
{
	t_token *current;

	current = shell()->lexer->tokens;
	if (ft_strcmp(current->value, "cd") == 0)
	{
		if (!current->next)
			cd(NULL);
		else
			cd(current->next->value);
	}
	if (ft_strcmp(current->value, "pwd") == 0)
		pwd();
	if (ft_strcmp(current->value, "echo") == 0)
	echo(current);
}
