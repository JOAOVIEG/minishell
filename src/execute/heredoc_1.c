/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:57:10 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/22 17:23:21 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	btree_create_node(t_node **target, char *redir, char *file2)
{
	*target = (t_node *)malloc(sizeof(t_node));
	if (*target == NULL)
	{
		status_error("minishell", "No memory", STDERR_FILENO);
		exit_shell(EXIT_FAILURE);
	}
	(*target)->type = TYPE_COMMAND;
	(*target)->left = NULL;
	(*target)->right = NULL;
	(*target)->cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	if ((*target)->cmd == NULL)
	{
		status_error("minishell", "No memory", STDERR_FILENO);
		exit_shell(EXIT_FAILURE);
	}
	(*target)->cmd->arg = (char **)malloc(sizeof(char *) * 2);
	(*target)->cmd->arg[0] = "cat";
	(*target)->cmd->arg[1] = NULL;
	(*target)->cmd->file = (char **)malloc(sizeof(char *) * 3);
	if ((*target)->cmd->file == NULL)
	{
		status_error("minishell", "No memory", STDERR_FILENO);
		exit_shell(EXIT_FAILURE);
	}
	apply_tmp_file(target, redir, file2);
}

void	apply_tmp_file(t_node **target, char *redir, char *file2)
{
	(*target)->cmd->file[0] = redir;
	(*target)->cmd->file[1] = file2;
	(*target)->cmd->file[2] = NULL;
	(*target)->cmd->heredoc = NULL;
	(*target)->cmd->valid_cmd_path = NULL;
	(*target)->cmd->path = NULL;
	(*target)->fd_in = STDIN_FILENO;
	(*target)->fd_out = STDOUT_FILENO;
}

t_node	*copy_tree(t_node *root)
{
	t_node	*new_node;

	if (root == NULL)
		return (NULL);
	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
	{
		status_error("minishell", "No memory", STDERR_FILENO);
		exit_shell(EXIT_FAILURE);
	}
	ft_memset(new_node, 0, sizeof(t_node));
	new_node->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (new_node->cmd == NULL)
	{
		status_error("minishell", "No memory", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_memset(new_node->cmd, 0, sizeof(t_cmd));
	(*new_node->cmd) = (*root->cmd);
	handle_assign(new_node, root);
	if (root->left)
		new_node->left = copy_tree(root->left);
	if (root->right)
		new_node->right = copy_tree(root->right);
	return (new_node);
}

void	handle_assign(t_node *new_node, t_node *root)
{
	new_node->cmd->arg = copy_string_array(root->cmd->arg);
	new_node->cmd->file = copy_string_array(root->cmd->file);
	new_node->cmd->heredoc = copy_string_array(root->cmd->heredoc);
	new_node->type = root->type;
	new_node->fd_in = root->fd_in;
	new_node->fd_out = root->fd_out;
}
