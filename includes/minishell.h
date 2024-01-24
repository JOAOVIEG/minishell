/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/24 16:31:05 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env			*v_env;
	char			*line;
	bool			signal_set;
	t_lexer			*lexer;
	t_parser		*parser;
}					t_shell;

void				cd(char *path);
void				echo(char **cmd);
void				pwd(void);
t_env				*add_env_var(t_env *env, char *name, char *value);
t_env				*find_env_var(t_env *env, char *name);
t_env				*env_cpy(char **envp);
void				ignore_signals(t_shell *minishell);
char				*read_input(void);
#endif
