/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:51:36 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/19 14:17:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*btree_search_item(t_node *root, char *data_ref, int (*cmpf)(char *,
			char *))
{
	t_node	*item;

	item = NULL;
	if (root != NULL)
	{
		item = btree_search_item(root->left, data_ref, cmpf);
		if (item == NULL && root->cmd->heredoc && cmpf(root->cmd->heredoc[0],
				data_ref) == 0)
			return (root);
		if (item == NULL)
			item = btree_search_item(root->right, data_ref, cmpf);
	}
	return (item);
}

// void	btree_apply_by_level(t_node *root, void (*applyf)(void *item,
// 			int current_level, int is_first_elem))
// {
// 	if (root == NULL)
// 		return ;
// }