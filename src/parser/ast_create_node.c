/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_create_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:22:22 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 19:46:46 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_astree	*ast_create_node(void *item, t_node_type type)
{
	t_astree	*node;

	node = (t_astree *)malloc(sizeof(t_astree));
	if (node == NULL)
		return (NULL);
	node->data = item;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
