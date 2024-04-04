/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:51:36 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/03 17:55:11 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void btree_create_node(t_node **target, char *redir, char *file2)
{
    *target = (t_node*)malloc(sizeof(t_node));
    if (*target == NULL)
    {
        status_error("minishell", "No memory", STDERR_FILENO);
        exit_shell(EXIT_FAILURE);
    }
    (*target)->type = TYPE_COMMAND;
    (*target)->left = NULL;
    (*target)->right = NULL;
    (*target)->cmd = (t_cmd*)malloc(sizeof(t_cmd));
    if ((*target)->cmd == NULL)
    {
        status_error("minishell", "No memory", STDERR_FILENO);
        exit_shell(EXIT_FAILURE);
    }
    (*target)->cmd->arg = NULL;
    (*target)->cmd->file = (char **)malloc(sizeof(char*) * 2); // Allocate space for 2 pointers
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
    (*target)->cmd->heredoc = NULL;
    (*target)->cmd->path = NULL;
    (*target)->cmd->cmd_path = NULL;
    (*target)->cmd->valid_cmd_path = NULL;
}

t_node *copy_tree(t_node *root)
{
	t_node *new_node;

    if (root == NULL)
        return NULL;
    new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
    {
        status_error("minishell", "No memory", STDERR_FILENO);
        exit_shell(EXIT_FAILURE);
    }
    new_node->cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (new_node->cmd == NULL)
    {
        status_error("minishell", "No memory", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    new_node->cmd->arg = copy_string_array(root->cmd->arg);
    new_node->cmd->file = copy_string_array(root->cmd->file);
    new_node->cmd->heredoc = copy_string_array(root->cmd->heredoc);
    new_node->type = root->type;
    new_node->fd_in = root->fd_in;
    new_node->fd_out = root->fd_out;
    new_node->left = copy_tree(root->left);
    new_node->right = copy_tree(root->right);
    return new_node;
}

char **copy_string_array(char **array)
{
    int count;
	int	i;
	char **new_array;

	count = 0;
	i = 0;
    if (array == NULL)
        return NULL;
    while (array[count] != NULL)
        count++;
    new_array = (char **)malloc((count + 1) * sizeof(char *));
    if (new_array == NULL)
    {
        status_error("minishell", "No memory", STDERR_FILENO);
        exit_shell(EXIT_FAILURE);
    }
    while (i < count)
	{
        new_array[i] = ft_strdup(array[i]);
		i++;
	}
    new_array[count] = NULL;

    return new_array;
}

void	ft_exec_piped_heredoc(t_node *node)
{
    t_node	*sub_hd_root;
	t_node *sub_node_hd;

	sub_node_hd = btree_search_item(node);
    sub_hd_root = find_parent(node, sub_node_hd);
	ft_execute(sub_hd_root);
    
    t_node *new_tree;
    t_node *new_sub_hd;
    
    new_tree = copy_tree(node);
    new_sub_hd = btree_search_item(new_tree);
    new_tree = apply_to_node(new_tree, new_sub_hd);
	shell()->heredoced = true;
	ft_execute(new_tree);
	unlink("temp");
}
