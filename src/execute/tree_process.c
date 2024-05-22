/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:17:04 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/17 17:17:37 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	right_tree_handle(t_node *node, int *pipe_end)
{
	pid_t	right_pid;
	int		r_status;

	right_pid = fork();
	right_node_process(node, pipe_end, right_pid);
	if (right_pid > 0)
	{
		close(pipe_end[0]);
		close(pipe_end[1]);
		waitpid(right_pid, &r_status, 0);
		if (WIFEXITED(r_status))
			shell()->status = WEXITSTATUS(r_status);
	}
}

void	left_tree_handle(t_node *node, int *pipe_end)
{
	int		l_status;
	pid_t	left_pid;

	left_pid = fork();
	left_node_process(node, pipe_end, left_pid);
	if (left_pid > 0)
	{
		waitpid(left_pid, &l_status, 0);
		if (WIFEXITED(l_status))
			shell()->status = WEXITSTATUS(l_status);
	}
}

void	handle_pipe_construct(int *pipe_end)
{
	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(EXIT_FAILURE);
	}
}
