/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/22 14:35:16 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*shell(void)
{
	static	t_shell minishell;
	
	return (&minishell);
}

void	ignore_signals()
{
	shell()->signal_set = true;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	read_input()
{
	shell()->line = readline("minishell> ");
	if (!shell()->line)
		exit(shell()->status);
}

int	main(int argc, char **argv, char **envp)
{
	// char **str = ft_split("hello ", ' ');
	// char *path = "includes";
	if (argc > 1)
	{
		if (access(argv[1], F_OK) == -1)
		{
			printf("minishell: %s: %s\n", argv[1], strerror(errno));
			return (EXIT_FAILURE);
		}
	}
    shell()->v_env = env_cpy(envp);
	shell()->status = 0;
	// ignore_signals();
    // while (1)
    // {
        // read_input();
		// echo(str);
		// pwd();
		// cd(path);
		// pwd();
		// env();
		// export("LOGNAME=will");
		unset("PATH");
		env();
		exit('\0');
    // }
    return (EXIT_SUCCESS);
}
