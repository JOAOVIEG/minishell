/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/22 14:24:12 by joaocard         ###   ########.fr       */
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
#include <errno.h>
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
	int		status;
	char	*line;
	bool	signal_set;
	//t_lexer_state lx_state;
}			t_shell;

void	cd(char *path);
void	echo(char **cmd);
void	pwd(void);
void	env(void);
void	exit_shell(char *arg);
void	free_env(void);
void	export(char *arg);
void	unset(char *arg);
t_env	*find_env_var(t_env *env, char *name);
t_env	*env_cpy(char **envp);
void	check_new_malloc(t_env *new);
void	new_var(t_env **head, t_env *tail, t_env *new);
void	get_var(t_env *new, char *envp, char *equal_pos);
void	ignore_signals();
void	read_input();
t_shell	*shell(void);
#endif
