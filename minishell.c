/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/18 15:15:48 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell		*shell(void)
{
	static	t_minishell minishell;

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
	char		*line;
	int			status;
	t_prompt	*shell_prompt;
	
	shell()->v_env = env_cpy(envp);
	// (void)argc;
	// (void)argv;
	// (void)envp;
	env_init(envp, shell);
	ignore_signals(minishell);
	status = 1;
	while (status)
	{
		line = read_input(minishell);

		

		
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(line, "pwd") == 0)
		{
			ft_putstr_fd(getcwd(NULL, 0), 1);
			ft_putstr_fd("\n", 1);
		}
		free(line);
	}
	free(minishell);
	return (EXIT_SUCCESS);
}

// criar uma funcao que limpe a minha struct principal
