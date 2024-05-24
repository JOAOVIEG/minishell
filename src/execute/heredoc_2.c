/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:23:08 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/22 17:24:22 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*btree_search_item(t_node *root)
{
	t_node	*item;

	if (root == NULL)
		return (NULL);
	if (root->cmd->heredoc != NULL)
		return (root);
	item = btree_search_item(root->left);
	if (item != NULL)
		return (item);
	return (btree_search_item(root->right));
}

int	btree_level_count(t_node *where, t_node *what)
{
	int	left;
	int	right;

	if (!where)
		return (-1);
	if (where == what)
		return (0);
	left = btree_level_count(where->left, what);
	if (left != -1)
		return (left + 1);
	right = btree_level_count(where->right, what);
	if (right != -1)
		return (right + 1);
	return (-1);
}
