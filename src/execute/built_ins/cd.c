/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:27 by joaocard          #+#    #+#             */
/*   Updated: 2024/05/22 11:16:42 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	cd(char *path)
{
	char	*oldpwd;
	t_env	*oldpwd_var;
	int		print_dir;

	print_dir = 0;
	oldpwd = getcwd(NULL, 0);
	oldpwd_var = NULL;
	if (!oldpwd)
		perror("getcwd");
	if (!path || strcmp(path, "-") == 0)
	{
		print_dir = print_flag_handle(path);
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
	pwd_handle(oldpwd, oldpwd_var);
}
