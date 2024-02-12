/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:32:27 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/12 18:25:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*create_cmd_from_string(char *str)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
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
	return (cmd);
}

t_node	*init_pipe_node(void)
{
	t_node	*pipe_node;

	pipe_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!pipe_node)
	{
		perror("Error: Failed to allocate memory for pipe_node");
		return (NULL);
	}
	pipe_node->type = TYPE_PIPE;
	pipe_node->cmd = create_cmd_from_string("|");
	return (pipe_node);
}

t_lst_tokens	*extract_left_tokens(t_shell *shell)
{
	t_lst_tokens	*left_tokens;
	t_lst_tokens	*current;

	left_tokens = NULL;
	current = shell->parser->tokens;
	while (current != NULL && current->type != TYPE_PIPE)
	{
		add_to_end(&left_tokens, current->data);
		current = current->next;
	}
	return (left_tokens);
}

t_lst_tokens	*extract_right_tokens(t_shell *shell)
{
	t_lst_tokens	*right_tokens;
	t_lst_tokens	*current;

	right_tokens = NULL;
	current = shell->parser->tokens;
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
	return (right_tokens);
}

void	build_tree_pipe(t_shell *shell)
{
	t_node			*pipe_node;
	t_lst_tokens	*left_tokens;
	t_lst_tokens	*right_tokens;

	pipe_node = init_pipe_node();
	left_tokens = extract_left_tokens(shell);
	right_tokens = extract_right_tokens(shell);
	if (left_tokens != NULL)
		pipe_node->left = new_tree_node(left_tokens);
	if (right_tokens != NULL)
		pipe_node->right = new_tree_node(right_tokens);
	free_lst_tokens(left_tokens);
	free_lst_tokens(right_tokens);
	shell->node = pipe_node;
}


