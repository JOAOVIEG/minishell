/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_simple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:41:57 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:59:32 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_tree_simple_command(t_shell *shell)
{
	shell->node = new_tree_node(shell->parser->tokens);
	shell->node->type = TYPE_COMMAND;
}
