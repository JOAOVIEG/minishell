/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/18 16:16:24 by joaocard         ###   ########.fr       */
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
	int		l_status;

	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(EXIT_FAILURE);
	}
	left_pid = fork();
	left_node_process(node, pipe_end, left_pid);
	if (left_pid > 0 && node->left->cmd->heredoc && !node->right->cmd->heredoc)
	{
		waitpid(left_pid, &l_status, 0);
		if (WIFEXITED(l_status))
			shell()->status = WEXITSTATUS(l_status);
	}
	right_pid = fork();
	if (left_pid > 0 && !node->left->cmd->heredoc && !reads_from_stdin(node->left))
		parent_pipe_exec_control(node, pipe_end, left_pid);
	right_node_process(node, pipe_end, right_pid);
	parent_pipe_exec_control(node, pipe_end, right_pid);
	if (left_pid > 0 && !node->left->cmd->heredoc && reads_from_stdin(node->left))
		parent_pipe_exec_control(node, pipe_end, left_pid);
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

int	reads_from_stdin(t_node *node)
{
	char	*cmd;

	cmd = node->cmd->arg[0];
	if (ft_strcmp(cmd, "cat") == 0 || ft_strcmp(cmd, "grep") == 0 \
		|| ft_strcmp(cmd, "awk") == 0 || ft_strcmp(cmd, "sed") == 0 \
		|| ft_strcmp(cmd, "wc") == 0 || ft_strcmp(cmd, "sort") == 0 \
		|| ft_strcmp(cmd, "uniq") == 0 || ft_strcmp(cmd, "cut") == 0 \
		|| ft_strcmp(cmd, "paste") == 0 || ft_strcmp(cmd, "tee") == 0 \
		|| ft_strcmp(cmd, "less") == 0 || ft_strcmp(cmd, "more") == 0)
		return (1);
	return (0);
}

// ls | echo Hello | <<end | pwd | wc -l
