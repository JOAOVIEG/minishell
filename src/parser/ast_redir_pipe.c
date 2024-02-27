#include "../../includes/minishell.h"

t_node	*redir_pipe_child_node(t_lst_tokens *tokens)
{
	t_node			*node;
	t_node			*rightmost_node;
	t_lst_tokens	*current;
	t_lst_tokens	*cmd_tokens;

	node = NULL;
	rightmost_node = NULL;
	current = tokens;
	while (current != NULL)
	{
		cmd_tokens = get_cmd_tokens(&current);
		if (!create_node_and_update_tree(&node, &rightmost_node, &cmd_tokens))
			return (NULL);
		if (current && current->type == TYPE_PIPE)
			current = current->next;
	}
	return (node);
}

t_node	*find_rightmost_tree_node(t_node *root)
{
	t_node	*rightmost;

	rightmost = root;
	while (rightmost->right != NULL)
		rightmost = rightmost->right;
	return (rightmost);
}

t_node	*build_redir_root_node(t_lst_tokens **current, t_node *tree_root)
{
	t_node	*node;
	t_cmd	*cmd;
	t_node	*rightmost;

	cmd = ft_calloc_memory(1, sizeof(t_cmd));
	cmd->arg = ft_calloc_memory(3, sizeof(char *));
	cmd->arg[0] = ft_strdup((*current)->data);
	*current = (*current)->next;
	cmd->arg[1] = ft_strdup((*current)->data);
	cmd->arg[2] = NULL;
	node = create_node(TYPE_REDIRECT, cmd, NULL, NULL);
	if (tree_root == NULL)
		node->right = tree_root;
	else
	{
		rightmost = find_rightmost_tree_node(tree_root);
		rightmost->right = node;
		node = tree_root;
	}
	return (node);
}

void	build_redir_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost;
	t_lst_tokens	*current;
	t_lst_tokens	*tail;
	t_lst_tokens	*lst_tk;

	tree_root = NULL;
	lst_tk = NULL;
	tail = NULL;
	current = shell->parser->tokens;
	while (current != NULL)
	{
		if (current->type == TYPE_REDIRECT)
		{
			tree_root = build_redir_root_node(&current, tree_root);
			current = current->next;
		}
		else
			lst_tk = build_redir_child_node(&current, &lst_tk, &tail);
	}
	rightmost = find_rightmost_tree_node(tree_root);
	rightmost->right = redir_pipe_child_node(lst_tk);
	define_direction(tree_root);
	shell->node = tree_root;
}
