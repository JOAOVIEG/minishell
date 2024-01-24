/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:41:03 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/24 16:45:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*node;

	node = (t_btree *)malloc(sizeof(t_btree));
	if (node == NULL)
		return (NULL);
	node->item = item;
	node->left = 0;
	node->right = 0;
	return (node);
}
