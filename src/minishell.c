/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/18 17:07:18 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*shell(void)
{
	static	t_shell minishell;

	return (&minishell);
}

void	ignore_signals(t_shell *minishell)
{
	minishell->signal_set = true;
	// ignore "Ctrl+C"
	signal(SIGINT, SIG_IGN);
	// ignore "Ctrl+Z"
	signal(SIGTSTP, SIG_IGN);
	// ignore "Ctrl+\"
	signal(SIGQUIT, SIG_IGN);
}

char	*read_input()
{
	shell()->line = readline("minishell> ");
	if (!shell()->line)
	{
		// Handle Ctrl+D
		exit(EXIT_SUCCESS);
	}
	return (shell()->line);
}

int	main(int argc, char **argv, char **envp)
{
	int			status;
	
	(void)argc;
	(void)argv;
	(void)envp;
	shell()->v_env = env_cpy(envp);
	ignore_signals(shell());
	status = 1;
	while (status)
	{
		read_input();
	}
	return (EXIT_SUCCESS);
}

