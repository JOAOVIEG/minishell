/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/16 13:36:11 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		printf("Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	shell->line = NULL;
	shell->signal_set = false;
	return (shell);
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
		// Handle Ctrl+D or other read errors
		exit(EXIT_SUCCESS);
	}
	return (minishell->line);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	t_shell	*minishell;
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	minishell = init_shell();
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

// criar uma struct principal para o minishell  com um ponteiro para a struct prompt

// na minha strcuct principal armazenar o input do user

// criar uma funcao que limpe a minha struct principal
