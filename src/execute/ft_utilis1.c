/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:17:09 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/25 16:58:41 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_file(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd->file[i])
	{
		node->fd_in = dup(STDIN_FILENO);
		node->fd_out = dup(STDOUT_FILENO);
		handle_file_redir(node, i++);
	}
}

void	invalid_cmd_path(t_node *node, char **env)
{
	if (env)
		ft_free_str_array(env);
	shell()->status = 127;
	if (str_is_only_whitespace(node->cmd->arg[0]) && node->cmd->arg[1])
		node->cmd->arg[0] = ft_strjoin(node->cmd->arg[0], node->cmd->arg[1]);
	status_error(node->cmd->arg[0], "command not found", STDERR_FILENO);
}

int	no_cmd_check(t_node *node, char **env)
{
	if (ft_strcmp(node->cmd->arg[0], ".") == 0 || ft_strcmp(node->cmd->arg[0],
			"..") == 0)
	{
		invalid_cmd_path(node, env);
		return (1);
	}
	if (input_is_dir(node, env) == 1)
		return (1);
	node->cmd->valid_cmd_path = get_cmd(node->cmd->cmd_path, node->cmd->arg[0]);
	if (node->cmd->valid_cmd_path == NULL)
	{
		invalid_cmd_path(node, env);
		return (1);
	}
	else
		return (0);
}

int	file_redir(t_node *node, int i)
{
	while (node->cmd->file && node->cmd->file[i] != NULL)
	{
		if (ft_strncmp(node->cmd->file[i], "<", 1) == 0)
			assign_fds(node);
		handle_file_redir(node, i);
		if (shell()->status != EXIT_SUCCESS)
			return (1);
		i++;
	}
	return (0);
}

void	heredoc_cmd_son(t_node *node)
{
	int	k;
	int	j;
	int	num_heredocs;

	k = 1;
	j = 0;
	num_heredocs = count_redir(node);
	while (k <= num_heredocs)
	{
		if (node->fd_in)
			close(node->fd_in);
		heredoc_check(node, j);
		j += 2;
		k++;
	}
}
