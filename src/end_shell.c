/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:36:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/05/22 21:01:58 by joaocard         ###   ########.fr       */
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
	if (shell()->new_tree)
		free_tree_node(&shell()->new_tree);
	if (shell()->history)
		free_history(shell()->history);
	if (shell()->v_env)
		free_env();
	if (shell()->env_arr)
		free_c_env(shell()->env_arr);
}
