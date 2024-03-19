/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/19 14:17:23 by joaocard         ###   ########.fr       */
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
		exit_shell(EXIT_SUCCESS);
	}
	else
		add_to_history(shell(), shell()->line);
}

int	main(int argc, char **argv, char **envp)
{
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
	return (EXIT_SUCCESS);
}
