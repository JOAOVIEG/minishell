/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/18 14:40:56 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell		*shell(void)
{
	static	t_minishell minishell;

	return (&minishell);
}

char	*read_input(void)
{
	char	*line;

	line = readline("");
	if (line && *line)
		add_history(line);
	return (line);
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
	status = 1;
	shell_prompt = set_prompt("minishell$ ");
	while (status)
	{
		printf("%s", shell_prompt->prompt_name);
		line = read_input();
		   if (!line)
        {
            // Handle Ctrl+D
            free(shell_prompt);
            exit(EXIT_SUCCESS);
        }
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			free(shell_prompt);
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(line, "pwd") == 0)
		{
			ft_putstr_fd(getcwd(NULL, 0), 1);
			ft_putstr_fd("\n", 1);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}

// criar uma struct principal para o minishell  com um ponteiro para a struct prompt

// na minha strcuct principal armazenar o input do user 

// criar uma funcao que limpe a minha struct principal 


