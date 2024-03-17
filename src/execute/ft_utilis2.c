/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:01:51 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 20:03:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_heredoc_proccess(t_node *node, char **env, int i)
{
	pid_t	pid;

	heredoc_cmd_son(node);
	while (node->cmd->file && node->cmd->file[i] != NULL)
		handle_file_redir(node, i++);
	if (no_cmd_check(node, env) == 1)
		exit_shell(shell()->status);
	pid = fork();
	assign_fds(node);
	run_path_process(node, pid, env);
	exit_shell(shell()->status);
}

void	heredoc_here(t_node *node, char **env, int i)
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error forking");
		shell()->status = EXIT_FAILURE;
		exit_shell(shell()->status);
	}
	else if (pid1 == 0)
		do_heredoc_proccess(node, env, i);
	else
		parent_control(node, pid1);
}

void	builtin_proccess(t_node *node)
{
	int		stdout;
	int		stdin;

	stdout = dup(STDOUT_FILENO);
	stdin = dup(STDIN_FILENO);
	redirections(node->fd_in, node->fd_out);
	run_builtin(node);
	dup2(stdout, STDOUT_FILENO);
	dup2(stdin, STDIN_FILENO);
	close(stdout);
	close(stdin);
}

void	do_builtin_file_handle(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd->file[i] != NULL)
	{
		if (ft_strncmp(node->cmd->file[i], "<", 1) == 0)
			assign_fds(node);
		handle_file_redir(node, i);
		i++;
	}
	if (shell()->status != EXIT_SUCCESS)
		return ;
	builtin_proccess(node);
}

void	builtin_heredoc_child(t_node *node, int i)
{
	int		num_heredocs;
	int		j;
	int		k;

	j = 0;
	k = 1;
	num_heredocs = count_redir(node);
	while (k <= num_heredocs)
	{
		if (node->fd_in)
			close(node->fd_in);
		heredoc_check(node, j);
		j += 2;
		k++;
	}
	while (node->cmd->file && node->cmd->file[i] != NULL)
	{
		handle_file_redir(node, i);
		i++;
	}
	assign_fds(node);
	redirections(node->fd_in, node->fd_out);
	run_builtin(node);
	child_control(node);
}
