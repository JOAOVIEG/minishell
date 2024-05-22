/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:51:36 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/22 17:22:19 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_string_array(char **array)
{
	int		count;
	int		i;
	char	**new_array;

	count = 0;
	i = 0;
	if (array == NULL)
		return (NULL);
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
	return (new_array);
}

void	free_tree(t_node **root)
{
	if (*root == NULL)
		return ;
	if ((*root)->left)
		free_tree(&(*root)->left);
	if ((*root)->right)
		free_tree(&(*root)->right);
	free_string_array(&(*root)->cmd->arg);
	free_string_array(&(*root)->cmd->heredoc);
	free_string_array(&(*root)->cmd->file);
	free((*root)->cmd);
	free(*root);
	*root = NULL;
}

void	free_string_array(char ***array_ptr)
{
	int	i;

	i = 0;
	if (*array_ptr == NULL)
		return ;
	while ((*array_ptr)[i] != NULL)
	{
		free((*array_ptr)[i]);
		i++;
	}
	free(*array_ptr);
	*array_ptr = NULL;
}

void	ft_exec_piped_heredoc(t_node *node)
{
	t_node	*sub_hd_root;
	t_node	*sub_node_hd;
	int		i;

	i = 1;
	sub_node_hd = btree_search_item(node);
	if (is_rightmost(node, btree_level_count_total(node), i))
		new_t_handle(node, sub_node_hd);
	else
	{
		sub_hd_root = find_parent(node, sub_node_hd);
		new_t_handle(node, sub_node_hd);
	}
}

void	new_t_handle(t_node *node, t_node *sub_node)
{
	t_node	*new_sub_hd;
	t_node	*new_sub_hd_root;
	t_node	*new_node;

	ft_execute(sub_node);
	new_node = copy_tree(node);
	new_sub_hd = btree_search_item(new_node);
	new_sub_hd_root = find_parent(new_node, new_sub_hd);
	new_node = apply_to_node(new_node, new_sub_hd_root);
	shell()->new_tree = new_node;
	ft_execute(shell()->new_tree);
	unlink("tmp");
}
