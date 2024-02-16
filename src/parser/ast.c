
#include "../../includes/minishell.h"

t_node	*create_node(t_token_type type, t_cmd *cmd, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)ft_calloc_memory(1, sizeof(t_node));
	node->type = type;
	node->cmd = cmd;
	node->left = left;
	node->right = right;
	return (node);
}

t_node	*init_pipe_node(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc_memory(1, sizeof(t_cmd));
	if (!cmd)
	{
		return (NULL);
	}
	cmd->arg = (char **)ft_calloc_memory(2, sizeof(char *));
	if (!cmd->arg)
	{
		free(cmd);
		return (NULL);
	}
	cmd->arg[0] = ft_strdup("|");
	cmd->arg[1] = NULL;
	return (create_node(TYPE_PIPE, cmd, NULL, NULL));
}

t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_node	*pipe_node;

	pipe_node = init_pipe_node();
	if (!pipe_node)
		return (NULL);
	pipe_node->left = left;
	pipe_node->right = right;
	pipe_node->fd_in = 0;
	pipe_node->fd_out = 1;
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
		if (!cmd_tokens)
			return ;
		new_node = create_new_node(&cmd_tokens);
		if (!new_node)
			return ;
		if (!tree_root)
		{
			tree_root = new_node;
			rightmost_node = new_node;
		}
		else
			update_tree_root(&tree_root, &rightmost_node,
				create_pipe_node(rightmost_node, new_node));
		if (current && current->type == TYPE_PIPE)
			current = current->next;
	}
	shell->node = tree_root;
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
	t_cmd	*cmd;

	cmd = create_cmd(tokens);
	if (!cmd)
		return (NULL);
	return (create_node(TYPE_COMMAND, cmd, NULL, NULL));
}

void	build_tree_simple_command(t_shell *shell)
{
	shell->node = new_tree_node(shell->parser->tokens);
	shell->node->type = TYPE_COMMAND;
	shell->node->fd_in = 0;
	shell->node->fd_out = 1;
}

void	build_tree(t_shell *shell)
{
	if (shell->parser->pipe_count == 0)
		build_tree_simple_command(shell);
	else if (shell->parser->pipe_count > 0)
		build_pipe_tree(shell);
	// print_tree(shell->node, 0, "root");
}
