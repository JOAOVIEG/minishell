/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/19 19:35:08 by wiferrei         ###   ########.fr       */
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
	t_node	*sub_node_hd;
	t_node	*dad_hd;
	//t_node	*ptr_dad;
	int		r_status;
	int		l_status;

	//ptr_dad = node;
	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(EXIT_FAILURE);
	}
	sub_node_hd = (t_node *)btree_search_item(node, "<<", (int(*)(char *, char *))ft_strcmp);
	if (!sub_node_hd)
	{
		left_pid = fork();
		left_node_process(node, pipe_end, left_pid);
		right_pid = fork();
		right_node_process(node, pipe_end, right_pid);
		parent_pipe_exec_control(node, pipe_end, right_pid, left_pid);
	}
	else if (sub_node_hd && shell()->pipe_call == 0)
	{
		shell()->pipe_call++;
		dad_hd = find_parent(node, sub_node_hd);
		//ptr_dad = dad_hd;
		left_pid = fork();
		left_node_process(dad_hd, pipe_end, left_pid);
		if (left_pid > 0)
		{
			close(pipe_end[1]);
			close(pipe_end[0]);
			waitpid(left_pid, &l_status, 0);
			if (WIFEXITED(l_status))
				shell()->status = WEXITSTATUS(l_status);
		}
		right_pid = fork();
		right_node_process(dad_hd, pipe_end, right_pid);
		if (right_pid > 0)
		{
			close(pipe_end[0]);
			close(pipe_end[1]);
			waitpid(right_pid, &r_status, 0);
			if (WIFEXITED(r_status))
				shell()->status = WEXITSTATUS(r_status);
		}
	}
	else if (shell()->pipe_call != 0)
	{
		left_pid = fork();
		left_node_process(node, pipe_end, left_pid);
		right_pid = fork();
		right_node_process(node, pipe_end, right_pid);
		parent_pipe_exec_control(node, pipe_end, right_pid, left_pid);
	}
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
	if (node->type == TYPE_COMMAND)
		ft_simple_cmds(node);
	if (node->type == TYPE_PIPE)
		ft_exec_piped(node);
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

