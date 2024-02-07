
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

t_ASTree	*new_tree_node(t_lst_tokens *tokens)
{
	int				i;
	t_lst_tokens	*current;
	t_ASTree		*tree_node;

	i = 0;
	current = tokens;
	tree_node = (t_ASTree *)ft_calloc(1, sizeof(t_ASTree));
	if (!tree_node)
		return (NULL);
	tree_node->data = (char **)ft_calloc(lst_token_size(tokens) + 1,
			sizeof(char *));
	if (!tree_node->data)
	{
		free(tree_node);
		return (NULL);
	}
	while (current != NULL)
	{
		tree_node->data[i] = ft_strdup(current->data);
		current = current->next;
		i++;
	}
	tree_node->left = NULL;
	tree_node->right = NULL;
	return (tree_node);
}


void	print_tree_node(t_ASTree *tree_node)
{
	int	i;

	i = 0;
	while (tree_node->data[i])
	{
		printf("%s\n", tree_node->data[i]);
		i++;
	}
}

void	tree_simple_command(t_parser *parser)
{
	parser->tree = new_tree_node(parser->tokens);
	print_tree_node(parser->tree);
}