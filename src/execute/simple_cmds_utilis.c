/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:50 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/04 16:19:23 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_node *node)
{
	char	*cmd;

	cmd = node->cmd->arg[0];
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (2);
}

void	exec_builtin(t_node *node)
{
	pid_t	heredoc_pid;
	int		i;

	i = 0;
	if (node->cmd->heredoc)
	{
		heredoc_pid = fork();
		heredoc_builtin_here(node, heredoc_pid, i);
	}
	else if (node->cmd->file && *node->cmd->file != NULL)
	{
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
	else
		builtin_proccess(node);
}

void	exec_cmd(t_node *node)
{
	pid_t	pid;
	int		i;

	i = 0;
	shell()->env_arr = env_list_to_arr();
	check_path(shell()->env_arr, node);
	if (node->cmd->heredoc)
		heredoc_here(node, shell()->env_arr, i);
	else
	{
		if (file_redir(node, i) == 1)
			return ;
		if (no_cmd_check(node, shell()->env_arr) == 1)
			return ;
		pid = fork();
		assign_fds(node);
		run_path_process(node, pid, shell()->env_arr);
	}
}
