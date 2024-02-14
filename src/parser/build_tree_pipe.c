/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:32:27 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/14 12:55:40 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_cmd_from_string(char *str)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = (char **)ft_calloc(2, sizeof(char *));
	if (!cmd->arg)
	{
		free(cmd);
		return (NULL);
	}
	cmd->arg[0] = ft_strdup(str);
	cmd->arg[1] = NULL;
	return (cmd);
}

t_node	*init_pipe_node(void)
{
	t_node	*pipe_node;

	pipe_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!pipe_node)
	{
		perror("Error: Failed to allocate memory for pipe_node");
		return (NULL);
	}
	pipe_node->type = TYPE_PIPE;
	pipe_node->cmd = create_cmd_from_string("|");
	return (pipe_node);
}

void	lst_tokenadd_back(t_lst_tokens **lst, t_lst_tokens *new)
{
	t_lst_tokens	*current;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_lst_tokens	*create_new_token(char *data, int type)
{
	t_lst_tokens	*new_token;

	new_token = (t_lst_tokens *)malloc(sizeof(t_lst_tokens));
	if (!new_token)
	{
		perror("Error: Failed to allocate memory for new_token");
		return (NULL);
	}
	new_token->data = strdup(data);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

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



t_lst_tokens	*get_cmd_tokens(t_lst_tokens **current)
{
	t_lst_tokens	*cmd_tokens;
	t_lst_tokens	*new_token;

	cmd_tokens = NULL;
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		new_token = create_new_token((*current)->data, (*current)->type);
		lst_tokenadd_back(&cmd_tokens, new_token);
		*current = (*current)->next;
	}
	return (cmd_tokens);
}

t_node	*create_new_node(t_lst_tokens **cmd_tokens)
{
	t_node	*new_node;

	new_node = new_tree_node(*cmd_tokens);
	free_lst_tokens(*cmd_tokens);
	*cmd_tokens = NULL;
	return (new_node);
}

t_node	*create_pipe_node(t_node *rightmost_node, t_node *new_node)
{
	t_node	*pipe_node;

	pipe_node = init_pipe_node();
	pipe_node->left = rightmost_node;
	pipe_node->right = new_node;
	return (pipe_node);
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

void	test_build_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_lst_tokens	*current;
	t_lst_tokens	*cmd_tokens;
	t_node			*new_node;
	t_node			*pipe_node;

	tree_root = NULL;
	rightmost_node = NULL;
	current = shell->parser->tokens;
	while (current != NULL)
	{
		cmd_tokens = get_cmd_tokens(&current);
		new_node = create_new_node(&cmd_tokens);
		if (tree_root == NULL)
		{
			tree_root = new_node;
			rightmost_node = new_node;
		}
		else
		{
			pipe_node = create_pipe_node(rightmost_node, new_node);
			update_tree_root(&tree_root, &rightmost_node, pipe_node);
		}
		if (current != NULL && current->type == TYPE_PIPE)
			current = current->next;
	}
	shell->node = tree_root;
}
