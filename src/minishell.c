/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/18 15:49:21 by wiferrei         ###   ########.fr       */
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

char	*read_input(t_shell *minishell)
{
	minishell->line = readline("minishell> ");
	if (!minishell->line)
	{
		// Handle Ctrl+D
		exit(EXIT_SUCCESS);
	}
	return (minishell->line);
}

int	main(int argc, char **argv, char **envp)
{
	int			status;
	
	//shell()->v_env = env_cpy(envp);

	//env_init(envp, shell);
	(void)argc;
	(void)argv;
	(void)envp;
	ignore_signals(shell());
	status = 1;
	while (status)
	{
		read_input(shell());

		

		
		
	}
	return (EXIT_SUCCESS);
}

// criar uma funcao que limpe a minha struct principal
