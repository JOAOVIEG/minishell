/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/05 14:06:53 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void ft_simple_cmds(t_node *node)
{	
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
	if ((left_pid = fork()) < 0)
	{
		perror("left fork failed");
		exit_shell(2);
	}
    if (left_pid == 0)
    {
        close(pipe_end[0]);
		node->left->fd_out = pipe_end[1];
		dup2(node->left->fd_out, STDOUT_FILENO);
        ft_execute(node->left);
		close(node->left->fd_out);
		close(pipe_end[1]);
		exit_shell(0);
    }
	if ((right_pid = fork()) < 0)
	{
		perror("right fork failed");
		exit_shell(3);
	}
    if (right_pid == 0)
    {
    	node->right->fd_in = pipe_end[0];
        close(pipe_end[1]);
		dup2(node->right->fd_in, STDIN_FILENO);
        ft_execute(node->right);
		close(node->right->fd_in);
		close(pipe_end[0]);
        exit_shell(0);
    }
    close(pipe_end[0]);
	// close(node->right->fd_in);
    close(pipe_end[1]);
	// close(node->left->fd_out);
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
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
	if (node->type == TYPE_COMMAND)
		ft_simple_cmds(node);
	if (node->type == TYPE_PIPE)
		ft_exec_piped(node);
}
