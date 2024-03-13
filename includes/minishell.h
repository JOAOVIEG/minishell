/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/13 15:54:57 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include "builtins.h"
# include "execute.h"
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/ioctl.h>

typedef struct s_history_entry
{
	char					*command;
	struct s_history_entry	*next;
}							t_history_entry;

typedef struct s_shell
{
	t_env					*v_env;
	bool					signal;
	int						status;
	char					*line;
	t_node					*node;
	t_lexer					*lexer;
	t_parser				*parser;
	t_history_entry			*history;
}							t_shell;

t_env						*find_env_var(t_env *env, char *name);
t_env						*env_cpy(char **envp);
void						check_new_malloc(t_env *new);
void						new_var(t_env **head, t_env *tail, t_env *new);
void						get_var(t_env *new, char *envp, char *equal_pos);
void						ignore_signals(void);
void						read_input(void);
t_shell						*shell(void);

// Free shell
void						reset_tree(void);
void						free_tree_cmd(t_cmd *cmd);
void						free_tree_node(t_node **tree_node);
void						end_shell(void);
void						free_shell(void);
#endif
