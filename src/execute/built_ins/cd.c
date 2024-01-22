/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:27 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/22 10:53:05 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*TODO*/
void	cd(char *path)
{
	char	*oldpwd;
	t_env	*pwd;
	t_env	*oldpwd_var;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("getcwd");
	if (!path)
	{
		path = find_env_var(shell()->v_env, "HOME")->value;
		if (!path)
		{
			perror("cd: HOME not set\n");
			return ;
		}
	}
	if (chdir(path) == -1)
			perror("cd");
	pwd = find_env_var(shell()->v_env, "PWD");
	oldpwd_var = find_env_var(shell()->v_env, "OLDPWD");
	if (pwd)
	{
		free(pwd->value);
		pwd->value = getcwd(NULL, 0);
	}
	if (oldpwd_var)
	{
		free(oldpwd_var->value);
		oldpwd_var->value = ft_strdup(oldpwd);
	}
	free(oldpwd);
}