/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/30 15:48:39 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"
# include "../../includes/lexer.h"
# include "../../includes/parser.h"

void	ft_execute(void)
{
	t_token *current;

	current = shell()->lexer->tokens;
	// if (!current->next)
	// {
	// 	printf("\033[1;31mSEGFAULT\n");
	// 	return ;
	// }
	printf("AQUI: %s\n", current->value);
	if (ft_strcmp(current->value, "cd") == 0)
		cd(current->next->value);
	if (ft_strcmp(current->value, "pwd") == 0)
		pwd();
}
