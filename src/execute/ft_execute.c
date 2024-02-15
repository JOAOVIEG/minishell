/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/15 14:18:55 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "../../includes/lexer.h"
// # include "../../includes/parser.h"
# include "../../includes/minishell.h"

void ft_simple_cmds(t_node *node)
{	
	/*if is a bultin executes builtin.
	else, ecxecutes form path*/
	if (is_builtin(node) == 1)
		exec_builtin(node);
	else if (is_builtin(node) == 0)
		return ;
	else if (is_builtin(node) == 2)
		exec_cmd(node);
}

void	ft_exec_piped(t_node *node)
{
	int		pipe_end[2];
	int		status;
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(pipe_end) < 0)
	{
		perror("Error at pipe");
		exit_shell(1);
	}
	node->left->fd_in = node->fd_in;
	close(node->fd_in);
	node->left->fd_out = pipe_end[1];
	node->right->fd_in = pipe_end[0];
	node->right->fd_out = node->fd_out;
	close(node->fd_out);
	if ((left_pid = fork()) < 0)
	{
		perror("Error at left fork");
		exit_shell(2);
	}
	else if (left_pid == 0)
	{
		close(pipe_end[0]);
		ft_execute(node->left);
		// close(pipe[1]);
		exit_shell(3);
	}
	if ((right_pid = fork()) < 0)
	{
		perror("Error at right fork");
		exit_shell(4); 
	}
	else if (right_pid == 0)
	{
		close(pipe_end[1]);
		ft_execute(node->right);
		// close(pipe_end[0]);
		exit_shell(5);
	}
	close(pipe_end[1]);
	close(pipe_end[0]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &status, 0);
	exit_shell((int)right_pid);
	close(node->left->fd_out);
	close(node->right->fd_in);
}

void	close_fds(int fd_i, int fd_o)
{
	if (fd_i != STDIN_FILENO)
		close(fd_i);
	if (fd_o != STDOUT_FILENO)
		close(fd_o);
}

int	redirections(int fd_i, int fd_o)
{
	if (redirect_in(fd_i) == -1 || redirect_out(fd_o) == -1)
		return (-1);
	return (0);
}

int	redirect_in(int fd_i)
{
	int red_i;
	
	if (fd_i == STDIN_FILENO)
		return (STDIN_FILENO);
	else
	{
		if ((red_i = dup2(fd_i, STDIN_FILENO)) < 0)
			return (-1);
		close(fd_i);
	}
	return (red_i);
}

int	redirect_out(int fd_o)
{
	int red_o;
	
	if (fd_o == STDOUT_FILENO)
		return (STDOUT_FILENO);
	else
	{
		if ((red_o = dup2(fd_o, STDOUT_FILENO)) < 0)
			return (-1);
		close(fd_o);
	}
	return (red_o);
}

void	ft_execute(t_node *node)
{
	/*Initializing the new variables fd_in and out for the
	simpliest case: one node cmd. Already taking into account pipe
	and other cases than simple commands*/
	shell()->node->fd_in = 0;
	shell()->node->fd_out = 1;
	/*if node is of type cmd*/
	ft_simple_cmds(node);
	/*if node is of type pipe*/
	// ft_exec_piped(node);
}
