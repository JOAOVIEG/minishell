/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_buid_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:12:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/24 17:56:57 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_btree	*btree_build_ast(t_token *tokens)
{
	t_btree	*root;
	t_token	*token;
	t_token	*left_start;
	t_token	*right_start;

	root = NULL;
	token = tokens;
	left_start = tokens;
	right_start = NULL;

	while (token != NULL)
	{
		if (ft_strcmp(token->value, "|") == 0)
		{
			root = btree_create_node(token);
			right_start = token->next;
			break;
		}
	}
	
}

// t_btree *build_ast(t_token *tokens) {
//     t_btree *root = NULL;
//     t_token *token = tokens;
//     t_token *left_start = tokens;
//     t_token *right_start = NULL;

//     // Traverse the list of tokens
//     while (token != NULL) {
//         // If the token is a pipe, create a new root node
//         if (strcmp(token->value, "|") == 0) {
//             root = btree_create_node(token);
//             right_start = token->next;
//             break;
//         }
//         token = token->next;
//     }

//     // If a pipe was found, create the left and right subtrees
//     if (root != NULL) {
//         root->left = build_ast_from_tokens(left_start, token);
//         root->right = build_ast_from_tokens(right_start, NULL);
//     }

//     return root;
// }

// t_btree *build_ast_from_tokens(t_token *start, t_token *end) {
//     // This function should build a subtree from the tokens between start and end
//     // This is a placeholder. You'll need to implement this function yourself.
//     return NULL;
//}