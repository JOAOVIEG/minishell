/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:36:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 14:24:42 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	end_shell(void)
{
	if (shell()->lexer)
		free_lexer(shell()->lexer);
	if (shell()->parser)
		free_parser(shell()->parser);
	if (shell()->node)
		free_tree_node(&shell()->node);
	if (shell()->history)
		free_history(shell()->history);
	if (shell()->v_env)
		free_env();
}
