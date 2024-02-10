
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


t_cmd *create_cmd_from_string(char *str)
{
    t_cmd *cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
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
    return cmd;
}

t_node *init_pipe_node()
{
    t_node *pipe_node = (t_node *)ft_calloc(1, sizeof(t_node));
    if (!pipe_node)
    {
        perror("Error: Failed to allocate memory for pipe_node");
        return NULL;
    }
    pipe_node->type = TYPE_PIPE;
    pipe_node->cmd = create_cmd_from_string("|");
    return pipe_node;
}

t_lst_tokens *extract_left_tokens(t_shell *shell)
{
    t_lst_tokens *left_tokens = NULL;
    t_lst_tokens *current = shell->parser->tokens;

    while (current != NULL && current->type != TYPE_PIPE)
    {
        add_to_end(&left_tokens, current->data);
        current = current->next;
    }
    return left_tokens;
}

t_lst_tokens *extract_right_tokens(t_shell *shell)
{
    t_lst_tokens *right_tokens = NULL;
    t_lst_tokens *current = shell->parser->tokens;

    // Skip tokens until the pipe token
    while (current != NULL && current->type != TYPE_PIPE)
        current = current->next;

    // Extract tokens for the right command
    if (current != NULL)
    {
        current = current->next;
        while (current != NULL)
        {
            add_to_end(&right_tokens, current->data);
            current = current->next;
        }
    }
    return right_tokens;
}

void free_tokens(t_lst_tokens *tokens)
{
    // Free memory allocated for the token list
    while (tokens != NULL)
    {
        t_lst_tokens *temp = tokens;
        tokens = tokens->next;
        free(temp);
    }
}

void build_tree_pipe(t_shell *shell)
{
    // Initialize variables
    t_node *pipe_node = init_pipe_node();
    t_lst_tokens *left_tokens = extract_left_tokens(shell);
    t_lst_tokens *right_tokens = extract_right_tokens(shell);

    // Construct left and right sub-trees
    if (left_tokens != NULL)
        pipe_node->left = new_tree_node(left_tokens);
    if (right_tokens != NULL)
        pipe_node->right = new_tree_node(right_tokens);

    // Clean up allocated memory
    free_tokens(left_tokens);
    free_tokens(right_tokens);

    shell->node = pipe_node;
}


void	build_tree(t_shell *shell)
{
    if (shell->parser->pipe_count == 0)
        build_tree_simple_command(shell);
    else if (shell->parser->pipe_count > 0)
        build_tree_pipe(shell); // Replace build_tree_pipes with build_tree_pipe
    printf("Root node:\n");
    print_tree_node(shell->node);
    printf("left node:\n");
    print_tree_node(shell->node->left);
    printf("right node:\n");
    print_tree_node(shell->node->right);
}