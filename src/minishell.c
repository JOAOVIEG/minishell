/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/02 10:01:04 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	check_heredoc(t_node *node)
{
	t_node	*sub_node_hd;
	int		hd_i;

	sub_node_hd = btree_search_item(node);
	hd_i = btree_level_count(node, sub_node_hd);
	if (node->type == TYPE_PIPE && hd_i > 1)
		return (1);
	if (node->type == TYPE_PIPE && hd_i == 0)
		return (2);
	return (0);
}

int	reads_from_stdin(t_node *node)
{
	char	*cmd;

	cmd = node->cmd->arg[0];
	if (!cmd)
		return (0);
	if (ft_strstr(cmd, "cat") != NULL || ft_strstr(cmd, "grep") != NULL
		|| ft_strstr(cmd, "sed") != NULL || ft_strstr(cmd, "awk") != NULL
		|| ft_strstr(cmd, "sort") != NULL || ft_strstr(cmd, "uniq") != NULL
		|| ft_strstr(cmd, "cut") != NULL || ft_strstr(cmd, "paste") != NULL
		|| ft_strstr(cmd, "wc") != NULL || ft_strstr(cmd, "tr") != NULL
		|| ft_strstr(cmd, "tee") != NULL || ft_strstr(cmd, "head") != NULL
		|| ft_strstr(cmd, "tail") != NULL || ft_strstr(cmd, "xargs") != NULL
		|| ft_strstr(cmd, "less") != NULL || ft_strstr(cmd, "more") != NULL
		|| ft_strstr(cmd, "cd") != NULL)
		return (1);
	return (0);
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
	int	arg_check;

	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
	{
		run_test_with_c_option(argv, envp);
		return (shell()->status);
	}
	arg_check = arg_access(argv, argc);
	if (arg_check != EXIT_SUCCESS)
		return (shell()->status);
	shell()->v_env = env_cpy(envp);
	while (1)
	{
		handle_signal(SIG_DEFAULT);
		shell()->pipe_call = 0;
		read_input();
		add_history(shell()->line);
		parser(shell());
		if (shell()->node)
		{
			if (check_heredoc(shell()->node) == 1)
				ft_exec_piped_heredoc(shell()->node);
			else
				ft_execute(shell()->node);
		}
		reset_parser_and_tree();
	}
	rl_clear_history();
	return (shell()->status);
}
