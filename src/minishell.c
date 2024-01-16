/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:27:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/16 11:50:55 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_input(void)
{
	char	*line;

	line = readline("Minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			status;
	

	(void)argc;
	(void)argv;
	(void)envp;
	status = 1;
	while (status)
	{
		line = read_input();
		   if (!line)
        {
            // Handle Ctrl+D
           
            exit(EXIT_SUCCESS);
        }
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
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


