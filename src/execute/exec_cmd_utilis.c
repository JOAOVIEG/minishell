/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:31:39 by joaocard          #+#    #+#             */
/*   Updated: 2024/04/03 14:01:36 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_path(char **env, t_node *node)
{
	node->cmd->path = get_path(env);
	if (node->cmd->path)
		node->cmd->cmd_path = ft_split(node->cmd->path, ':');
}

char	*get_cmd(char **cmd_path, char *cmd)
{
	char	*path_cpy;

	if ((*cmd && cmd[0] == '/') || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) == 0)
		{
			path_cpy = ft_strdup(cmd); 
			return (path_cpy);
		}
		else
		{
			perror("Error get_command");
			shell()->status = 1;
		}
	}
	else
	{
		if (cmd_path)
			return (validate_cmd(cmd_path, cmd));
		else
		{
			perror("Error");
			shell()->status = 1;
		}
	}
	return (NULL);
}

char	*get_path(char **env)
{
	char	**tmp;

	if (*env == NULL)
	{
		perror("ERROR env at path");
		free_c_env(env);
		shell()->status = EXIT_FAILURE;
		return (NULL);
	}
	else
	{
		tmp = env;
		while (*tmp && ft_strncmp("PATH", *tmp, 4))
			tmp++;
		if (*tmp == NULL)
		{
			perror("ERROR env at path");
			// free_c_env(env);
			//This line is commented out because is causing a double free error
			shell()->status = EXIT_FAILURE;
			return (NULL);
		}
		return (*tmp + 5);
	}
}

char	*validate_cmd(char **cmd_paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (*cmd && cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		tmp2 = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(tmp2, F_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	free_cmd_paths(cmd_paths);
	return (NULL);
}
