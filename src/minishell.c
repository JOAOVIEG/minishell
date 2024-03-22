/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/22 16:14:43 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../includes/builtins.h"
#include "../includes/minishell.h"

t_shell	*shell(void)
{
	static t_shell	minishell;

	if (!minishell.lexer)
		minishell.lexer = init_lexer();
	if (!minishell.parser)
		minishell.parser = init_parser();
	return (&minishell);
}

void	read_input(void)
{
	char	*rprompt;

	rprompt = "\001\033[38;5;208m\002minishell:$ \001\033[0m\002";
	shell()->line = readline(rprompt);
	if (!shell()->line)
	{
		if (isatty(0))
			ft_putstr_fd("exit\n", 2);
		exit_shell(shell()->status);
	}
	else
		add_to_history(shell(), shell()->line);
}

void	run_test_with_c_option(char **argv, char **envp)
{
	shell()->v_env = env_cpy(envp);
	shell()->status = 0;
	handle_signal(SIG_DEFAULT);
	shell()->pipe_call = 0;
	shell()->line = argv[2];
	add_history(shell()->line);
	parser(shell());
	if (shell()->node)
		ft_execute(shell()->node);
	reset_parser_and_tree();
	rl_clear_history();
	free_lexer(shell()->lexer);
	free_parser(shell()->parser);
	free_env();
	exit(shell()->status);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc > 2 && strcmp(argv[1], "-c") == 0)
	{
		run_test_with_c_option(argv, envp);
		return (shell()->status);
	}
	if (argc > 1)
	{
		if (access(argv[1], F_OK) == -1)
		{
			printf("minishell: %s: %s\n", argv[1], strerror(errno));
			shell()->status = errno;
			return (shell()->status);
		}
	}
	shell()->v_env = env_cpy(envp);
	shell()->status = 0;
	while (1)
	{
		handle_signal(SIG_DEFAULT);
		shell()->pipe_call = 0;
		read_input();
		add_history(shell()->line);
		parser(shell());
		if (shell()->node)
			ft_execute(shell()->node);
		reset_parser_and_tree();
	}
	rl_clear_history();
	return (shell()->status);
}
