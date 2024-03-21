/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:51:36 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/21 18:37:04 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*btree_search_item(t_node *root, char *data_ref, int (*cmpf)(char *,
			char *))
{
	t_node	*item;

	item = NULL;
	if (root != NULL)
	{
		item = btree_search_item(root->left, data_ref, cmpf);
		if (item == NULL && root->cmd->heredoc && cmpf(root->cmd->heredoc[0],
				data_ref) == 0)
			return (root);
		if (item == NULL)
			item = btree_search_item(root->right, data_ref, cmpf);
	}
	return (item);
}

int	btree_level_count(t_node *where, t_node *what)
{
	int	left;
	int	right;

	if (!where)
		return (-1);
	if (where == what)
		return (0);
	left = btree_level_count(where->left , what);
	if (left != -1)
		return (left + 1);
	right = btree_level_count(where->right, what);
	if (right != -1)
		return (right + 1);
	return (-1);
}

void	apply_to_node(t_node *root, t_node *target, void(*func)(t_node*))
{
	if (root == NULL)
		return ;
	if (root == target)
	{
		func(root);
		return ;
	}
	apply_to_node(root->left, target, func);
	apply_to_node(root->right, target, func);
}

void btree_create_node(t_node **target)
{
    *target = (t_node*)malloc(sizeof(t_node));
    if (*target == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    (*target)->type = TYPE_COMMAND;
    (*target)->left = NULL;
    (*target)->right = NULL;

    (*target)->cmd = (t_cmd*)malloc(sizeof(t_cmd));
    if ((*target)->cmd == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    (*target)->cmd->arg = NULL;

    (*target)->cmd->file = (char **)malloc(sizeof(char*) * 2); // Allocate space for 2 pointers
    if ((*target)->cmd->file == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    (*target)->cmd->file[0] = strdup(">tmp"); // Duplicate the string
    (*target)->cmd->file[1] = NULL; // Null-terminate the array

    (*target)->cmd->heredoc = NULL;
    (*target)->cmd->path = NULL;
    (*target)->cmd->cmd_path = NULL;
    (*target)->cmd->valid_cmd_path = NULL;
}

t_node *copy_tree(t_node *root)
{
    if (root == NULL)
        return NULL;

    // Allocate memory for new node
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for new cmd
    new_node->cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (new_node->cmd == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    // Copy data from root to new_node
    // Replace with your data copy logic if needed
    new_node->cmd->arg = copy_string_array(root->cmd->arg);
    new_node->cmd->file = copy_string_array(root->cmd->file);
    new_node->cmd->heredoc = copy_string_array(root->cmd->heredoc);
    new_node->type = root->type;
    new_node->fd_in = root->fd_in;
    new_node->fd_out = root->fd_out;

    // Recursively copy left and right subtrees
    new_node->left = copy_tree(root->left);
    new_node->right = copy_tree(root->right);

    return new_node;
}

char **copy_string_array(char **array)
{
    if (array == NULL)
        return NULL;

    // Count the number of strings in the array
    int count = 0;
    while (array[count] != NULL)
        count++;

    // Allocate memory for the new array
    char **new_array = (char **)malloc((count + 1) * sizeof(char *));
    if (new_array == NULL)
    {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    // Copy the strings
    for (int i = 0; i < count; i++)
        new_array[i] = ft_strdup(array[i]);

    // Null-terminate the new array
    new_array[count] = NULL;

    return new_array;
}

void	ft_exec_piped_heredoc(t_node *node, t_node *sub_node_hd)
{
    int		pipe_end[2];
    pid_t	left_pid;
    pid_t	right_pid;
    t_node	*sub_hd_root;

    if (pipe(pipe_end) < 0)
    {
        perror("Error at pipe");
        exit_shell(EXIT_FAILURE);
    }
    sub_hd_root = find_parent(node, sub_node_hd);
    left_pid = fork();
    if (left_pid < 0)
    {
        perror("Error at fork");
        exit_shell(EXIT_FAILURE);
    }
    left_node_process(sub_hd_root, pipe_end, left_pid);
	if (sub_hd_root->right)
	{
		right_pid = fork();
		if (right_pid < 0)
		{
			perror("Error at fork");
			exit_shell(EXIT_FAILURE);
		}
		right_node_process(sub_hd_root, pipe_end, right_pid);
		parent_pipe_exec_control(sub_hd_root, pipe_end, right_pid, left_pid);
	}
    
    // int	sub_hd_root_index;
    
    // sub_hd_root_index = btree_level_count(node, sub_hd_root) - 1;
    
    t_node *new_tree;
    t_node *new_sub_hd;
    t_node *new_sub_hd_root;
    
    new_tree = copy_tree(node);
    new_sub_hd = btree_search_item(new_tree, "<<", (int(*)(char *, char *))ft_strcmp);
    new_sub_hd_root = find_parent(new_tree, new_sub_hd);
    apply_to_node(new_tree, new_sub_hd_root, (void(*)(t_node *))btree_create_node);
    if (pipe(pipe_end) < 0)
    {
        perror("Error at pipe");
        exit_shell(EXIT_FAILURE);
    }
    left_pid = fork();
    if (left_pid < 0)
    {
        perror("Error at fork");
        exit_shell(EXIT_FAILURE);
    }
    left_node_process(new_tree, pipe_end, left_pid);
    right_pid = fork();
    if (right_pid < 0)
    {
        perror("Error at fork");
        exit_shell(EXIT_FAILURE);
    }
    right_node_process(new_tree, pipe_end, right_pid);
    parent_pipe_exec_control(new_tree, pipe_end, right_pid, left_pid);
}
	// if (pipe(pipe_end) < 0)
	// {
	// 	perror("Error at pipe");
	// 	exit_shell(EXIT_FAILURE);
	// }
	// else if (sub_node_hd && shell()->pipe_call == 0)
	// {
	// 	shell()->pipe_call++;
	// 	dad_hd = find_parent(node, sub_node_hd);
	// 	//ptr_dad = dad_hd;
	// 	left_pid = fork();
	// 	left_node_process(dad_hd, pipe_end, left_pid);
	// 	if (left_pid > 0)
	// 	{
	// 		close(pipe_end[1]);
	// 		close(pipe_end[0]);
	// 		waitpid(left_pid, &l_status, 0);
	// 		if (WIFEXITED(l_status))
	// 			shell()->status = WEXITSTATUS(l_status);
	// 	}
	// 	right_pid = fork();
	// 	right_node_process(dad_hd, pipe_end, right_pid);
	// 	if (right_pid > 0)
	// 	{
	// 		close(pipe_end[0]);
	// 		close(pipe_end[1]);
	// 		waitpid(right_pid, &r_status, 0);
	// 		if (WIFEXITED(r_status))
	// 			shell()->status = WEXITSTATUS(r_status);
	// 	}
	// }