/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:31:44 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 19:22:57 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ast_free_node(t_astree *node)
{
	if (node == NULL)
		return ;
	if (node->type && NODE_DATA)
		free(node->data);
	ast_free_node(node->left);
	ast_free_node(node->right);
	free(node);
}