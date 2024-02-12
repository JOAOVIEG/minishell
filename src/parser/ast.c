
#include "../../includes/minishell.h"

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

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = (char **)ft_calloc(lst_token_size(tokens) + 2, sizeof(char *));
	if (!cmd->arg)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	current = tokens;
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

	tree_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!tree_node)
		return (NULL);
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
void	print_tree_node(t_node *tree_node)
{
	int	i;

	if (tree_node == NULL || tree_node->cmd == NULL)
	{
		printf("Error: tree_node or tree_node->cmd is NULL\n");
		return ;
	}
	i = 0;
	while (tree_node->cmd->arg[i])
	{
		printf("%s\n", tree_node->cmd->arg[i]);
		i++;
	}
}

void	build_tree_simple_command(t_shell *shell)
{
	shell->node = new_tree_node(shell->parser->tokens);
	shell->node->type = TYPE_COMMAND;
	shell->node->fd_in = dup(0);
	shell->node->fd_out = dup(1);
	// print_tree_node(shell->node);
}





void	build_tree(t_shell *shell)
{
    if (shell->parser->pipe_count == 0)
        build_tree_simple_command(shell);
    else if (shell->parser->pipe_count > 0)
        build_tree_pipe(shell); 
    printf("Root node:\n");
    print_tree_node(shell->node);
    printf("left node:\n");
    print_tree_node(shell->node->left);
    printf("right node:\n");
    print_tree_node(shell->node->right);
}