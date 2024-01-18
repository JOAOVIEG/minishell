/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/18 16:42:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include  "lexer.h"

typedef struct s_env 
{
	char			*name;
	char			*value;
	struct s_env	*next;	
}	t_env;

typedef struct s_shell
{
	t_env	*v_env;
	char	*line;
	bool	signal_set;
	//t_lexer_state lx_state;
}			t_shell;

void	cd(char *path);
void	echo(char **cmd);
void	pwd(void);
t_env	*add_env_var(t_env *env, char *name, char *value);
t_env	*find_env_var(t_env *env, char *name);
t_env	*env_cpy(char **envp);
void	ignore_signals(t_shell *minishell);
char	*read_input();
t_shell	*shell(void);
#endif
