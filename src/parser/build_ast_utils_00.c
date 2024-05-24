/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils_00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:48:52 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:58:42 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*find_parent(t_node *root, t_node *node)
{
	t_node	*parent;

	if (root == NULL)
		return (NULL);
	if (root->left == node || root->right == node)
		return (root);
	parent = find_parent(root->left, node);
	if (parent != NULL)
		return (parent);
	return (find_parent(root->right, node));
}

void	update_tree_root(t_node **tree_root, t_node **rightmost_node,
		t_node *pipe_node)
{
	t_node	*parent;

	if (*rightmost_node == *tree_root)
		*tree_root = pipe_node;
	else
	{
		parent = find_parent(*tree_root, *rightmost_node);
		parent->right = pipe_node;
	}
	*rightmost_node = pipe_node->right;
}

t_lst_tokens	*get_cmd_tokens(t_lst_tokens **current)
{
	t_lst_tokens	*cmd_tokens;
	t_lst_tokens	*tail;
	t_lst_tokens	*new_token;

	cmd_tokens = NULL;
	tail = NULL;
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		new_token = ft_calloc_memory(1, sizeof(t_lst_tokens));
		if (!new_token)
			return (NULL);
		new_token->data = ft_strdup((*current)->data);
		if (!new_token->data)
		{
			free(new_token);
			return (NULL);
		}
		new_token->type = (*current)->type;
		new_token->next = NULL;
		lst_tokenadd_back(&cmd_tokens, &tail, new_token);
		*current = (*current)->next;
	}
	return (cmd_tokens);
}

t_cmd	*create_cmd(t_lst_tokens *tokens)
{
	int				i;
	t_lst_tokens	*current;
	t_cmd			*cmd;

	i = 0;
	current = tokens;
	cmd = (t_cmd *)ft_calloc_memory(1, sizeof(t_cmd));
	cmd->arg = (char **)ft_calloc_memory(lst_token_size(tokens) + 1,
			sizeof(char *));
	while (current != NULL)
	{
		cmd->arg[i] = ft_strdup(current->data);
		current = current->next;
		i++;
	}
	cmd->arg[i] = NULL;
	cmd->file = NULL;
	cmd->heredoc = NULL;
	return (cmd);
}

t_node	*new_tree_node(t_lst_tokens *tokens)
{
	t_cmd	*cmd;

	cmd = create_cmd(tokens);
	if (!cmd)
		return (NULL);
	return (create_node(TYPE_COMMAND, cmd, NULL, NULL));
}
