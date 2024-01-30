/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 18:29:38 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"
#include "../includes/minishell.h"

t_shell	*shell(void)
{
	static t_shell	minishell;

	if (!minishell.lexer)
		minishell.lexer = init_lexer();
	// if (!minishell.parser)
	// 	minishell.parser = init_parser();
	return (&minishell);
}

void	ignore_signals(void)
{
	shell()->signal_set = true;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	read_input(void)
{
	shell()->line = readline("minishell>");
	if (!shell()->line)
		end_shell();
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
	{
		if (access(argv[1], F_OK) == -1)
		{
			printf("minishell: %s: %s\n", argv[1], strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	(void)envp;
	//shell()->v_env = env_cpy(envp);
	shell()->status = 0;
	ignore_signals();
	while (1)
	{
		read_input();
		init_lexer_state(&shell()->lexer->state, shell()->line);
		tokenize_input(shell()->lexer);
		free_token_list(shell()->lexer->tokens);
		free(shell()->line);
	}
	return (EXIT_SUCCESS);
}
