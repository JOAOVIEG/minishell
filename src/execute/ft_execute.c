/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/21 18:31:54 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_simple_cmds(t_node *node)
{
	no_cmd_file_redir(node);
	if (node->cmd->arg[0] == NULL)
		return ;
	else if (is_builtin(node) == 1)
		exec_builtin(node);
	else if (is_builtin(node) == 2)
		exec_cmd(node);
}

void	ft_exec_piped(t_node *node)
{
	int		pipe_end[2];
	pid_t	left_pid;
	pid_t	right_pid;
	// t_node	*sub_node_hd;
	// int		hd_i;
	
	// sub_node_hd = btree_search_item(node, "<<", (int(*)(char *, char *))ft_strcmp);
	// hd_i = btree_level_count(node, sub_node_hd);
	// // if (!sub_node_hd || btree_level_count(node, sub_node_hd) - 1 > 0)
	// // 	return ;
	
	// if (sub_node_hd && hd_i == 0)
	// {
	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(EXIT_FAILURE);
	}
	left_pid = fork();
	left_node_process(node, pipe_end, left_pid);
	right_pid = fork();
	right_node_process(node, pipe_end, right_pid);
	parent_pipe_exec_control(node, pipe_end, right_pid, left_pid);
}

void	heredoc_check(t_node *node, int i)
{
	if (node->cmd && node->cmd->heredoc)
	{
		node->fd_in = heredoc(node, i);
		if (node->fd_in < 0)
		{
			printf("erro\n");
			shell()->status = EXIT_FAILURE;
			exit_shell(shell()->status);
		}
	}
}

void	ft_execute(t_node *node)
{
	/*I need to get a function that searches a heredoc that is not in the
	root level*/
	t_node	*sub_node_hd;
	int		hd_i;
	sub_node_hd = btree_search_item(node, "<<", (int(*)(char *, char *))ft_strcmp);
	hd_i = btree_level_count(node, sub_node_hd);
	if (node->type == TYPE_PIPE && hd_i > 1)
		ft_exec_piped_heredoc(node, sub_node_hd);
	else if (node->type == TYPE_PIPE || (node->type == TYPE_PIPE && hd_i == 1))
		ft_exec_piped(node);
	else if (node->type == TYPE_COMMAND)
		ft_simple_cmds(node);
}

void	heredoc_builtin_here(t_node *node, pid_t pid, int i)
{
	if (pid < 0)
	{
		perror("Error forking");
		shell()->status = EXIT_FAILURE;
		exit_shell(shell()->status);
	}
	else if (pid == 0)
		builtin_heredoc_child(node, i);
	else
		parent_control(node, pid);
}

// cat >first | echo Hello | <<end | pwd | cat | wc -l >last

