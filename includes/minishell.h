/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/06 13:03:45 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include "lexer.h"
# include "parser.h"
# include <errno.h>
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
	int				status;
	char			*line;
	bool			signal_set;
	t_lexer			*lexer;
	t_parser		*parser;
}					t_shell;

t_env				*find_env_var(t_env *env, char *name);
t_env				*env_cpy(char **envp);
void				check_new_malloc(t_env *new);
void				new_var(t_env **head, t_env *tail, t_env *new);
void				get_var(t_env *new, char *envp, char *equal_pos);
void				ignore_signals(void);
void				read_input(void);
t_shell				*shell(void);
void				parser(t_shell *shell);

void				end_shell(void);
#endif
