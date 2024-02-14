
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


void print_tree(t_node *node, int depth, char* side)
{
    if (node == NULL)
        return;

    // Print the indentation
    for (int i = 0; i < depth; i++)
        printf("\t");

    // Print the side (left or right)
    printf("├──%s(", side);

    // Print the command
    for (int i = 0; node->cmd->arg[i] != NULL; i++)
    {
        printf("%s ", node->cmd->arg[i]);
    }

    printf(")\n");

    // Recursively print the left and right children
    print_tree(node->left, depth + 1, "left");
    print_tree(node->right, depth + 1, "right");
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
        test_build_pipe_tree(shell);
    print_tree(shell->node, 0, "root");
}