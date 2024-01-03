/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/03 16:30:41 by wiferrei         ###   ########.fr       */
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
# include "structs.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

//global variable
extern int	g_last_exit_code;

// src/clean.c
void	free_ptr(void *ptr);

// src/env.c
int	get_env_var_index(char **env, char *var);

// src/init_data.c

bool	init_env(t_data *data, char **env);
bool	init_data(t_data *data, char **env);

// src/error.c

bool	usage_message(bool return_val);
void	exit_shell(t_data *data, int exno);
int	error_message_cmd(char *command, char *detail, char *error_msg,
		int error_nbr);
#endif
