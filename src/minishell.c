/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/10 19:36:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"
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

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	add_to_history(t_shell *shell, char *command)
{
	t_history_entry	*new_entry;

	new_entry = ft_calloc(1, sizeof(t_history_entry));
	new_entry->command = ft_strdup(command);
	new_entry->next = shell->history;
	shell->history = new_entry;
}

void	read_input(void)
{
	shell()->line = \
		readline("\001\033[38;5;208m\002minishell:$ \001\033[0m\002");
	if (!shell()->line)
	{
		write(1, "exit\n", 5);
		shell()->status = EXIT_SUCCESS;
		exit_shell(shell()->status);
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
	ignore_signals();
	while (1)
	{
		read_input();
		add_history(shell()->line);
		parser(shell());
		if (shell()->node)
			ft_execute(shell()->node);
		printf("%d\n", shell()->status);
		reset_tree();
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
