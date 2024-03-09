/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:36:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/09 17:28:26 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	end_shell(void)
{
	// free(shell()->v_env);
	// free(shell()->line);
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
	exit(shell()->status);
}

// void	free_shell(void)
// {
// 	if (shell()->lexer)
// 		free_lexer(shell()->lexer);
// 	if (shell()->parser)
// 	{
// 		free_parser(shell()->parser);
// 		shell()->parser = NULL;
// 	}
// 	if (shell()->node)
// 		free_tree_node(&shell()->node);
// 	if (shell()->history)
// 	{
// 		free_history(shell()->history);
// 		shell()->history = NULL;
// 	}
// 	if (shell()->v_env)
// 		free_env();
// }
