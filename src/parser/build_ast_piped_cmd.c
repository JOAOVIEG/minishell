/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_piped_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:51:43 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:59:10 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*init_pipe_node(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc_memory(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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
	return (pipe_node);
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

t_node	*create_node_and_update_tree(t_node **tree_root,
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
			create_pipe_node(*rightmost_node, new_node));
	return (new_node);
}

void	build_pipe_tree(t_shell *shell)
{
	t_node			*tree_root;
	t_node			*rightmost_node;
	t_lst_tokens	*current;
	t_lst_tokens	*cmd_tokens;

	tree_root = NULL;
	rightmost_node = NULL;
	current = shell->parser->tokens;
	while (current != NULL)
	{
		cmd_tokens = get_cmd_tokens(&current);
		if (!cmd_tokens)
			return ;
		if (!create_node_and_update_tree(&tree_root, &rightmost_node,
				&cmd_tokens))
			return ;
		if (current && current->type == TYPE_PIPE)
			current = current->next;
	}
	shell->node = tree_root;
}
