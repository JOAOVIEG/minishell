/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/17 14:33:40 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "../../includes/lexer.h"
// # include "../../includes/parser.h"
#include "../../includes/minishell.h"

void	ft_simple_cmds(t_node *node)
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
    pid_t	left_pid;
    pid_t	right_pid;

    if (pipe(pipe_end) < 0)
    {
        perror("Error at pipe");
        exit_shell(1);
    }
    node->left->fd_in = node->fd_in;
    node->left->fd_out = pipe_end[1];
    node->right->fd_in = pipe_end[0];
    node->right->fd_out = node->fd_out;
	if ((left_pid = fork()) < 0)
	{
		perror("left fork failed");
		exit_shell(2);
	}
    if (left_pid == 0)
    {
        close(pipe_end[0]);
        if ((node->right->type == TYPE_COMMAND) && is_builtin(node->left) == 1)
        {
            dup2(node->left->fd_out, STDOUT_FILENO);
            exec_builtin(node->left);
        }
        else if (is_builtin(node->left) == 2)
        {
            ft_execute(node->left);
        }
        exit(0);
    }
	if ((right_pid = fork()) < 0)
	{
		perror("right fork failed");
		exit_shell(3);
	}
    if (right_pid == 0)
    {
        close(pipe_end[1]);
        if ((node->right->type == TYPE_COMMAND) && is_builtin(node->right) == 1)
        {
            dup2(node->right->fd_in, STDIN_FILENO);
            exec_builtin(node->right);
        }
        else if (is_builtin(node->right) == 2)
        {
            ft_execute(node->right);
        }
        exit_shell(0);
    }
    close(pipe_end[0]);
    close(pipe_end[1]);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
}

ft_exec_redirectin(t_node *node)
{
	pid_t	right_node;
	node->right->fd_in = node->fd_in;
	node->right->fd_out = node->fd_out;
	if ((right_node = fork()) < 0)
	{
		perror("right_node fork failed");
		exit_shell(0);
	}
	if (right_node == 0)
	{
		if ((node->right->type == TYPE_COMMAND) && is_builtin(node->right) == 1)
		{
			dup2(node->right->right, STDIN_FILENO);
			if (node->right->fd_out != STDOUT_FILENO);
				dup2(node->right->fd_out, STDOUT_FILENO);
			exec_builtin(node->right);
		}
		else if (is_builtin(node->right) == 2)
			ft_execute(node->right);
		exit_shell(1);
	}
	close_fds(node->fd_in, node->fd_out);
	close_fds(node->right->fd_in, node->right->fd_out);
	waitpid(right_node, NULL, 0);
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
	int	red_i;

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
	int	red_o;

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
	/*shell()->node->fd_in = 0;
	shell()->node->fd_out = 1;*/
	if (node->type == TYPE_COMMAND)
		ft_simple_cmds(node);
	if (node->type == TYPE_PIPE)
		ft_exec_piped(node);
}
