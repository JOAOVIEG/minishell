/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/19 15:28:46 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell		*shell(void)
{
	static	t_shell minishell;

	if (!minishell.lexer)
		minishell.lexer = init_lexer();
		

	return (&minishell);
}

void	ignore_signals(t_shell *minishell)
{
	minishell->signal_set = true;
	// ignore "Ctrl+C"
	signal(SIGINT, SIG_IGN);
	// ignore "Ctrl+\"
	signal(SIGQUIT, SIG_IGN);
}

char	*read_input()
{
	shell()->line = readline("minishell>");
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
	//shell()->v_env = env_cpy(envp);
	ignore_signals(shell());
	status = 1;
	while (status)
	{
		read_input();
		

		init_lexer_state(&shell()->lexer->state, shell()->line);
		tokenize_input(shell()->lexer);
		// printing the input saved  in the lexer
		// Now I need start split the tokens
		//printf("%s\n", shell()->lexer->state.input);

	}
	return (EXIT_SUCCESS);
}

