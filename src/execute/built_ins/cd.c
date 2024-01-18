/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:27 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/18 14:42:52 by joaocard         ###   ########.fr       */
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
			return (EXIT_FAILURE);
		}
	}
	if (chdir(path) == -1)
			perror("cd");
	/*If the directory change is successful, cd sets the value of the PWD environment
	variable to the new directory name, and sets the OLDPWD environment variable
	to the value of the current working directory before the change.
	The return status is zero if the directory is successfully changed, non-zero oth-
	erwise.*/
	pwd = find_env_var(shell()->v_env, "PWD");
	// oldpwd_var = fi
}