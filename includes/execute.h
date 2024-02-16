/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:21:37 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/15 16:17:20 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include "parser.h"

typedef struct s_cmd
{
	char			**arg;
	char			*path;
	char			**cmd_path;
	char			*valid_cmd_path;
}					t_cmd;

typedef struct s_node
{
	t_cmd			*cmd;
	t_token_type	type;
	int				fd_in;
	int				fd_out;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

void				ft_execute(void);
void				ft_simple_cmds(void);
void				exec_cmd(void);
char				**env_list_to_arr(void);
void				check_path(char **env);
char				*get_path(char **env);
void				free_c_env(char **env);
char				*get_cmd(char **cmd_path, char *cmd);
char				*validate_cmd(char **cmd_paths, char *cmd);
#endif