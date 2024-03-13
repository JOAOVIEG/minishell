/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:10:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/13 17:57:26 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_eof(void)
// {
// 	write(1, "exit\n", 5);
// 	shell()->status = EXIT_SUCCESS;
// 	exit_shell(shell()->status);
// }

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	ignore_signals(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }

// int	g_status;

// void	handle_sigint(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		g_status = 130;
// 		ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 	}
// }

void	default_sigint(int sig)
{
	(void)sig;
	shell()->status = 130;
    shell()->signal = true;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}


void	hdsig(int sig)
{
	(void)sig;
    dprintf(1, "\n");
    rl_on_new_line();
    rl_replace_line("", 1);
	//kill (getpid(), SIGKILL);
    rl_redisplay();
}

// void	sig_parent(int sig)
// {
// 	if (sig == SIGINT)
// 		dprintf(1, "\n");
// 	else if (sig == SIGQUIT)
// 		dprintf(2, "Quit (code dumped)\n");
// }

void	handle_signal(int state)
{
	if (state == SIG_DEFAULT)
	{
		signal(SIGINT, default_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == SIG_HEREDOC)
	{
		signal(SIGINT, hdsig);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (state == SIG_CHILD)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (state == SIG_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}