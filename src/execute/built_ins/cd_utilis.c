/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:12 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/17 15:34:09 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_home_var(char *path)
{
	path = find_env_var(shell()->v_env, "HOME")->value;
	if (!path)
	{
		shell()->status = errno;
		return (strerror(errno));
	}
	return (path);
}

void	update_pwd(t_env *pwd)
{
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
}

void	update_oldpwd(t_env *oldpwd_var, char *oldpwd)
{
	free(oldpwd_var->value);
	oldpwd_var->value = ft_strdup(oldpwd);
}

int	print_flag_handle(char *path)
{
	int		print_dir;

	if (!path)
		print_dir = 0;
	else
		print_dir = 1;
	return (print_dir);
}

void	pwd_handle(char *oldpwd, t_env *oldpwd_var)
{
	t_env	*pwd;

	pwd = find_env_var(shell()->v_env, "PWD");
	oldpwd_var = find_env_var(shell()->v_env, "OLDPWD");
	if (pwd)
		update_pwd(pwd);
	if (oldpwd_var)
		update_oldpwd(oldpwd_var, oldpwd);
	free(oldpwd);
}
