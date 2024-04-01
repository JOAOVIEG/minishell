/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:17 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/01 17:50:36 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

typedef struct s_exp_buff	t_exp_buff;

typedef struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*next;
}							t_env;

void						cd(char *path);
char						*get_home_var(char *path);
void						update_pwd(t_env *pwd);
void						update_oldpwd(t_env *oldpwd_var, char *oldpwd);
int							echo(char **cmd);
int							flag_handle(char **cmd);
int							to_print(char **cmd);
void						pwd(void);
void						env(void);
void						exit_shell(int status);
int							ft_in_is_digit(char *in);
void						ft_exit(char **arg);
void						free_env(void);
void						export(char **arg);
int							is_invalid_variable(char *name);
bool						verify_env_name(t_exp_buff *data);
t_env						*create_var(t_env *new, char *name, char *value);
t_env						*update_envl(t_env *env, t_exp_buff *data);
t_env						*concatenate_envl(t_env *env_list,
								t_exp_buff *data);
void						display_exp_var(t_env *env);
int							unset(char **arg);
void						backshift(char **env, int start);
void						update_env_list(char **env);
long long int				ft_atol(const char *av);

#endif