/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rightmost_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:51:59 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 16:54:15 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_astree	*get_rightmost_node(t_astree *node)
{
	if (node == NULL)
		return (NULL);
	else if (node->right == NULL)
		return (node);
	else
		return (get_rightmost_node(node->right));
}