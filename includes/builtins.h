/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:17 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/07 17:21:13 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;


void	cd(char *path);
char	*get_home_var(char *path);
void	update_pwd(t_env *pwd);
void	update_oldpwd(t_env *oldpwd_var, char *oldpwd);
void	echo(char **cmd);
void	pwd(void);
void	env(void);
void	exit_shell(char **arg);
void	free_env();
void	export(char **arg);
char	*get_equal(char *arg);
t_env	*create_var(t_env *new, char *name, char *value);
char	*get_var_name(char *arg, char *equal);
t_env	*update_envl(t_env *env, t_env *new, char *name, char *value);
char	*get_var_value(t_env *env, char *name);
void	display_exp_var(t_env *env);
void	unset(char **arg);
t_env	*unset_var(t_env *head);
int		is_builtin();
void	exec_builtin();
#endif