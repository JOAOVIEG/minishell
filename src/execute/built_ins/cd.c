/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:27 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/05 16:07:32 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd(char *path)
{
	char	*oldpwd;
	t_env	*pwd;
	t_env	*oldpwd_var;
	int		print_dir;

	print_dir = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("getcwd");
	if (!path || strcmp(path, "-") == 0)
	{
		if (!path)
			print_dir = 0;
		else
			print_dir = 1;
		oldpwd_var = find_env_var(shell()->v_env, "OLDPWD");
		if (oldpwd_var && oldpwd_var->value)
			path = oldpwd_var->value;
		else
			path = get_home_var(path);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		shell()->status = 1;
	}
	else if (print_dir)
		printf("%s\n", path);
	pwd = find_env_var(shell()->v_env, "PWD");
	oldpwd_var = find_env_var(shell()->v_env, "OLDPWD");
	if (pwd)
		update_pwd(pwd);
	if (oldpwd_var)
		update_oldpwd(oldpwd_var, oldpwd);
	free(oldpwd);
}

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
