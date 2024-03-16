/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:30:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/16 21:01:13 by joaocard         ###   ########.fr       */
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
	if (left_pid > 0)
	{
		waitpid(left_pid, &l_status, 0);
		if (WIFEXITED(l_status))
			shell()->status = WEXITSTATUS(l_status);
		if (node->right->cmd->heredoc)
		{
			close(pipe_end[0]);
			pipe_end[0] = -1;
		}
	}
	// if (pipe_end[0] == -1)
	// {
	// 	if (pipe(pipe_end) < 0)
	// 	{
	// 		perror("Error at pipe");
	// 		exit_shell(EXIT_FAILURE);
	// 	}
	// }
	right_pid = fork();
	assign_fds(node->right);
	right_node_process(node, pipe_end, right_pid);
	parent_pipe_exec_control(node, pipe_end, right_pid);
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
/*test THIS cases


minishell:$ <<end | <<out <<i
out
i
end
minishell:$ <<end | <<out |<< a
a
out
end
minishell:$ <<end | <<out |<< a
end
minishell:$ <<end | <<out |<< a
out
a
end
minishell:$ <<end | <<out |<< a
end
minishell:$ 



*/

//TODO: CORRECT MULTIPLE HEREDOCS FOR EXECMD AND EXEC_BUILTIN