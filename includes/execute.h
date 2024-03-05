/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:21:37 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/05 14:06:06 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include "parser.h"

typedef struct s_cmd
{
	char			**arg;
	char			**file;
	char			**heredoc;
	// expasion $USER
	// here_doc -> <<delim
	// append -> >>file
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

void	ft_execute(t_node *node);
void	ft_simple_cmds(t_node *node);
int		is_builtin(t_node *node);
void	exec_builtin(t_node *node);
void	exec_cmd(t_node *node);
void	free_cmd_paths(char **cmd_paths);
char	**env_list_to_arr();
int		redirections(int fd_i, int fd_o);
int		redirect_in(int fd_i);
int		redirect_out(int fd_o);
void	close_fds(int fd_i, int fd_o);
void	check_path(char **env, t_node *node);
char	*get_path(char **env);
void	free_c_env(char **env);
char	*get_cmd(char **cmd_path, char *cmd);
char	*validate_cmd(char **cmd_paths, char *cmd);
void	ft_exec_piped(t_node *node);
int		heredoc(t_node *node);
char	*read_from_stdin(char *delim, char	*buffer, size_t buffer_size);
void	error_msg();
void	*ft_my_realloc(void *ptr, size_t size);
#endif