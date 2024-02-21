#include "../../includes/minishell.h"

t_node	*init_redir_node(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc_memory(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = (char **)ft_calloc_memory(2, sizeof(char *));
	if (!cmd->arg)
	{
		free_tree_cmd(cmd);
		return (NULL);
	}
	cmd->arg[0] = NULL;
	cmd->arg[1] = NULL;
	return (create_node(TYPE_REDIRECT, cmd, NULL, NULL));
}

t_node	*create_redir_node(t_node *redirection_node, t_node *right)
{
	redirection_node->right = right;
	return (redirection_node);
}

t_node	*create_node_and_update_redir_tree(t_node **tree_root,
		t_node **rightmost_node, t_lst_tokens **cmd_tokens)
{
	t_node	*new_node;

	new_node = create_new_node(cmd_tokens);
	if (!new_node)
		return (NULL);
	if (!*tree_root)
	{
		*tree_root = new_node;
		*rightmost_node = new_node;
	}
	else
		update_tree_root(tree_root, rightmost_node,
			create_redir_node(*rightmost_node, new_node));
	return (new_node);
}

void	open_file(t_node *node)
{
	if (!node || !node->cmd || !node->cmd->arg[0] || !node->cmd->arg[1])
		return ;
	if (node->type == TYPE_REDIRECT)
	{
		if (ft_strcmp(node->cmd->arg[0], "<") == 0)
		{
			node->fd_in = open(node->cmd->arg[1], O_RDONLY);
			if (node->fd_in == -1)
				perror("Error opening file");
			node->fd_out = 1;
		}
		else if (ft_strcmp(node->cmd->arg[0], ">") == 0)
		{
			node->fd_in = 0;
			node->fd_out = open(node->cmd->arg[1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (node->fd_out == -1)
				perror("Error opening file");
		}
	}
}
void	define_direction(t_node *node)
{
	if (!node)
		return ;
	
	if (node->type == TYPE_REDIRECT)
	{
		if (ft_strcmp(node->cmd->arg[0], "<") == 0)
		{
			node->type = TYPE_REDIRECT_IN;
		}
		else if (ft_strcmp(node->cmd->arg[0], ">") == 0)
		{
			node->type = TYPE_REDIRECT_OUT;
		}
	}
	define_direction(node->left);
	define_direction(node->right);
}
void	build_redir_tree(t_shell *shell)
{
	t_node *tree_root;
	t_node *rightmost_node;
	t_lst_tokens *current;
	t_lst_tokens *redir_tokens;
	t_cmd *cmd;
	t_node *redir_node;

	tree_root = NULL;
	rightmost_node = NULL;
	current = shell->parser->tokens;
	while (current != NULL)
	{
		if (current->type == TYPE_REDIRECT)
		{
			cmd = ft_calloc_memory(1, sizeof(t_cmd));
			cmd->arg = ft_calloc_memory(3, sizeof(char *));
			cmd->arg[0] = ft_strdup(current->data);
			current = current->next;
			cmd->arg[1] = ft_strdup(current->data);
			cmd->arg[2] = NULL;
			redir_node = create_node(TYPE_REDIRECT, cmd, NULL, NULL);
			redir_node->right = tree_root;
			tree_root = redir_node;
			rightmost_node = redir_node;
			current = current->next;
		}
		else
		{
			redir_tokens = get_cmd_tokens(&current);
			if (!redir_tokens)
				return ;
			if (!create_node_and_update_redir_tree(&tree_root, &rightmost_node,
					&redir_tokens))
				return ;
		}
	}
	define_direction(tree_root);
	// open_file(tree_root);
	shell->node = tree_root;
}