/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/09 14:21:53 by joaocard         ###   ########.fr       */
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

void	ignore_signals(void)
{
	shell()->signal_set = true;
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	read_input(void)
{
	char *str;

	// char *home;
	// str = getcwd(NULL, 0);
	// home = getenv("HOME");
	// if (home && !ft_strncmp(str, home, ft_strlen(home)))
	// {
	// 	str += ft_strlen(home);
	// 	str = ft_strjoin("minishell:~", str);	
	// }
	// else
	// 	str = ft_strjoin("minishell:", str);
	// str = ft_strjoin(str, "$ ");
	str = "minishell> ";
	shell()->line = readline(str);
	if (!shell()->line)
	{
		write_history(".msh_hist");
		rl_clear_history();
		exit(shell()->status);
	}
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
	read_history(".msh_hist"); // ILLEGAL FUNCTIONS
	shell()->v_env = env_cpy(envp);
	shell()->status = 0;
	// ignore_signals();
	while (1)
    {
        read_input();
        add_history(shell()->line);
        // init_lexer_state(&shell()->lexer->state, shell()->line);
        // tokenize_input(shell()->lexer);
		// ft_execute(node);
		// free_tokens();
    }
	// free_env();
	write_history(".msh_hist"); // ILLEGAL FUNCTIONS
    rl_clear_history();
	return (EXIT_SUCCESS);
}

void	free_tokens()
{
	t_token	*curr;
	t_token	*tmp;
	
	curr = shell()->lexer->tokens;
	while (curr)
	{
		tmp = curr->next;
		free(curr->value);
		curr->value = 0;
		free(curr);
		curr = tmp;
	}
	shell()->lexer->tokens = NULL;
}
