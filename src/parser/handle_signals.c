/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:10:01 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 21:06:44 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sig_shell	*sig_shell(void)
{
	static t_sig_shell	shell;

	return (&shell);
}

void	sig_shell_init(void)
{
	shell()->status = 0;
	shell()->signal = false;
}

void	default_sigint(int sig)
{
	(void)sig;
	shell()->status = 130;
	shell()->signal = true;
	sig_shell()->status = 130;
	shell()->signal = true;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	hdsig(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	shell()->status = 130;
	shell()->signal = true;
	sig_shell()->status = 130;
	shell()->signal = true;
	rl_on_new_line();
	rl_replace_line("", 1);
	exit_shell(shell()->status);
	rl_redisplay();
}

void	child_sigint(int sig)
{
	(void)sig;
	shell()->status = 130;
	shell()->signal = true;
	sig_shell()->status = 130;
	shell()->signal = true;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

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
		signal(SIGQUIT, child_sigint);
		signal(SIGINT, SIG_DFL);
	}
	else if (state == SIG_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
