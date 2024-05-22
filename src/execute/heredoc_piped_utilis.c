/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped_utilis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:27:38 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/22 16:02:50 by joaocard         ###   ########.fr       */
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

bool	is_rightmost(t_node *node, int lvs, int i)
{
	bool	value;
	
	if (node == NULL)
		return (false);
	if (node->cmd->heredoc != NULL && i == lvs)
	{
		value = true;
		return (value);
	}
	i++;
	return (is_rightmost(node->right, lvs, i));
}

int btree_level_count_total(t_node *root)
{
	int	right_height;

    if (root == NULL)
        return (0);
    else
    {
        right_height = btree_level_count_total(root->right);
        	return(right_height + 1);
    }
}

t_node	*apply_to_node(t_node *root, t_node *target)
{
	t_node	*new_node;

	if (root == NULL)
		return (NULL);
	if (root->right == target)
	{
		free_tree_node(&root->right->left);
		free_tree_node(&root->right->right);
		// free_tree
		btree_create_node(&new_node, ">", "tmp");
		root->right = new_node;
	}
	else
		apply_recur(root, target);
	return (root);
}

void	apply_recur(t_node *root, t_node *target)
{
	root->left = apply_to_node(root->left, target);
	root->right = apply_to_node(root->right, target);
}

void	my_free_tree(t_node *root)
{
	if (root == NULL)
		return ;
	my_free_tree(root->left);
	my_free_tree(root->right);
	free(root);
}
