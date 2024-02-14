
#include "../../includes/minishell.h"

t_node	*init_pipe_node(void)
{
	t_node	*pipe_node;
	t_cmd	*cmd;

	pipe_node = (t_node *)ft_calloc_memory(1, sizeof(t_node));
	cmd = (t_cmd *)ft_calloc_memory(1, sizeof(t_cmd));
	cmd->arg = (char **)ft_calloc_memory(2, sizeof(char *));
	cmd->arg[0] = ft_strdup("|");
	cmd->arg[1] = NULL;
	pipe_node->type = TYPE_PIPE;
	pipe_node->cmd = cmd;
	return (pipe_node);
}

t_node	*create_pipe_node(t_node *rightmost_node, t_node *new_node)
{
	t_node	*pipe_node;

	pipe_node = init_pipe_node();
	pipe_node->left = rightmost_node;
	pipe_node->right = new_node;
	return (pipe_node);
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

t_node	*create_new_node(t_lst_tokens **cmd_tokens)
{
	t_node	*new_node;

	new_node = new_tree_node(*cmd_tokens);
	new_node->type = TYPE_COMMAND;
	free_lst_tokens(*cmd_tokens);
	*cmd_tokens = NULL;
	return (new_node);
}

void	build_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_lst_tokens	*current;
	t_lst_tokens	*cmd_tokens;
	t_node			*new_node;

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
			update_tree_root(&tree_root, &rightmost_node,
				create_pipe_node(rightmost_node, new_node));
		if (current != NULL && current->type == TYPE_PIPE)
			current = current->next;
	}
	shell->node = tree_root;
}

int	lst_token_size(t_lst_tokens *tokens)
{
	int				count;
	t_lst_tokens	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
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
	return (cmd);
}

t_node	*new_tree_node(t_lst_tokens *tokens)
{
	t_node	*tree_node;

	tree_node = (t_node *)ft_calloc_memory(1, sizeof(t_node));
	tree_node->cmd = create_cmd(tokens);
	if (!tree_node->cmd)
	{
		free(tree_node);
		return (NULL);
	}
	tree_node->left = NULL;
	tree_node->right = NULL;
	return (tree_node);
}

void	build_tree_simple_command(t_shell *shell)
{
	shell->node = new_tree_node(shell->parser->tokens);
	shell->node->type = TYPE_COMMAND;
	shell->node->fd_in = dup(0);
	shell->node->fd_out = dup(1);
}

void	build_tree(t_shell *shell)
{
	if (shell->parser->pipe_count == 0)
		build_tree_simple_command(shell);
	else if (shell->parser->pipe_count > 0)
		build_pipe_tree(shell);
	print_tree(shell->node, 0, "root");
}
