/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmds_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:18:50 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/12 12:01:08 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_node *node)
{
	char	*cmd;

	cmd = node->cmd->arg[0];
	if (ft_strcmp(cmd, "cd") == 0 || \
			ft_strcmp(cmd, "pwd") == 0 || \
			ft_strcmp(cmd, "echo") == 0 || \
			ft_strcmp(cmd, "export") == 0 || \
			ft_strcmp(cmd, "unset") == 0 || \
			ft_strcmp(cmd, "env") == 0 || \
			ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (2);
}

void	exec_builtin(t_node *node)
{
	int		i;

	if (node->cmd->heredoc)
	{
		if (!node->fd_in)
			node->fd_in = heredoc(node);
	}
	if (node->cmd->file && *node->cmd->file != NULL)
	{
		i = 0;
		while (node->cmd->file && node->cmd->file[i] != NULL)
		{
			assign_fds(node);
			handle_file_redir(node, i);
			i++;
		}
		if (shell()->status == EXIT_SUCCESS)
			run_process(node);
	}
	else
		run_builtin(node);
}

void	exec_cmd(t_node *node)
{
	char	**env;
	pid_t	pid;
	int		i;

	i = 0;
	if (node->cmd->heredoc && !node->fd_in)
		node->fd_in = heredoc(node);
	assign_fds(node);
	env = env_list_to_arr();
	check_path(env, node);
	while (node->cmd->file && node->cmd->file[i] != NULL)
	{
		handle_file_redir(node, i);
		i++;
	}
	pid = fork();
	run_path_process(node, pid, env);
}
