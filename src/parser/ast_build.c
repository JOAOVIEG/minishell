/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:45:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 20:04:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_astree	*build_ast(t_token *tokens)
{
	t_astree	*root;
	t_astree	*node;
	t_astree	*rightmost;
	t_token		*token;

	root = NULL;
	node = NULL;
	rightmost = NULL;
	token = tokens;
	while (token != NULL)
	{
		if (token->type == CHAR_PIPE)
		{
			node = ast_create_node(token, NODE_PIPE);
			node->left = root;
			node->right = build_ast(token->next);
			root = node;
			break ;
		}
		else
		{
			node = ast_create_node(token, NODE_DATA);
			if (root == NULL && node->type != NODE_PIPE)
				root = node;
			else
			{
				rightmost = get_rightmost_node(root);
				rightmost->right = node;
			}
		}
		token = token->next;
	}
	printf("root->data: %s\n", (char *)root->data);
	return (root);
}

