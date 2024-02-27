#include "../../includes/minishell.h"

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

// t_node	*build_redir_root_node(t_lst_tokens **current, t_node *tree_root)
// {
// 	t_node	*node;
// 	t_cmd	*cmd;

// 	cmd = ft_calloc_memory(1, sizeof(t_cmd));
// 	cmd->arg = ft_calloc_memory(3, sizeof(char *));
// 	cmd->arg[0] = ft_strdup((*current)->data);
// 	*current = (*current)->next;
// 	cmd->arg[1] = ft_strdup((*current)->data);
// 	cmd->arg[2] = NULL;
// 	node = create_node(TYPE_REDIRECT, cmd, NULL, NULL);
// 	node->right = tree_root;
// 	return (node);
// }

t_lst_tokens	*build_redir_child_node(t_lst_tokens **current,
		t_lst_tokens **cmd_tokens, t_lst_tokens **tail)
{
	t_lst_tokens	*new_token;

	if (*current != NULL && (*current)->type != TYPE_REDIRECT)
	{
		new_token = ft_calloc_memory(1, sizeof(t_lst_tokens));
		new_token->data = ft_strdup((*current)->data);
		new_token->type = (*current)->type;
		new_token->next = NULL;
		lst_tokenadd_back(cmd_tokens, tail, new_token);
	}
	*current = (*current)->next;
	return (*cmd_tokens);
}

void	build_redir_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_lst_tokens	*current;
	t_lst_tokens	*cmd_tokens;
	t_lst_tokens	*tail;

	tree_root = NULL;
	current = shell->parser->tokens;
	cmd_tokens = NULL;
	tail = NULL;
	while (current != NULL)
	{
		if (current->type == TYPE_REDIRECT)
		{
			tree_root = build_redir_root_node(&current, tree_root);
			current = current->next;
		}
		else
			cmd_tokens = build_redir_child_node(&current, &cmd_tokens, &tail);
	}
	tree_root->right = new_tree_node(cmd_tokens);
	tree_root->right->type = TYPE_COMMAND;
	define_direction(tree_root);
	shell->node = tree_root;
}
