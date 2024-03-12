/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:21:37 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/12 16:01:03 by joaocard         ###   ########.fr       */
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
void	no_cmd_file_redir(t_node *node);
int		is_dir(t_node *node);
int		is_dir_i(t_node *node, int i);
int		input_is_dir(t_node *node, char **env);
void	ft_simple_cmds(t_node *node);
int		is_builtin(t_node *node);
void	exec_builtin(t_node *node);
void	exec_cmd(t_node *node);
void	free_cmd_paths(char **cmd_paths);
char	**env_list_to_arr(void);
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
char	*read_from_stdin(char **delim, char	*buffer, size_t buffer_size);
void	error_msg(void);
void	*ft_my_realloc(void *ptr, size_t size);
void	run_builtin(t_node *node);
void	parent_control(t_node *node, pid_t pid);
void	child_control(t_node *node);
void	run_process(t_node *node);
void	assign_fds(t_node *node);
int		open_append_to(t_node *node, int i);
int		open_file_to(t_node *node, int i);
int		open_file_from(t_node *node, int i);
void	handle_file_redir(t_node *node, int i);
void	parent_exec_control(t_node *node, pid_t pid, char **env);
void	free_paths(t_node *node);
void	child_exec_process(t_node *node, char **env, int i);
void	run_path_process(t_node *node, pid_t pid, char **env);
void	parent_pipe_exec_control(t_node *node, int pipe_end[2], \
	pid_t left_pid, pid_t right_pid);
void	execute_right_node(t_node *node, int pipe_end[2]);
void	execute_left_node(t_node *node, int pipe_end[2]);
void	right_node_process(t_node *node, int pipe_end[2], pid_t right_pid);
void	left_node_process(t_node *node, int pipe_end[2], pid_t left_pid);
void	heredoc_check(t_node *node);
void	get_file_append(t_node *node);
void	get_file(t_node *node);
void	status_error(char *what, char *message, int	fd);
#endif