/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utilis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:31:39 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/27 18:08:43 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	check_path(char **env, t_node *node)
{
	node->cmd->path = get_path(env);
	if (node->cmd->path)
		node->cmd->cmd_path = ft_split(node->cmd->path, \
			':');
}

char *get_cmd(char **cmd_path, char *cmd)
{
	if (*cmd && cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			perror("Error get_command");
	}
	else
	{
		if (cmd_path)
			return (validate_cmd(cmd_path, cmd));
		else
			perror ("Error");
	}
	return (NULL);
}

char	*get_path(char **env)
{
	if (*env == NULL)
	{
		perror("ERROR env at path");
		// free_env();
		free_c_env(env);
		exit(EXIT_FAILURE);
	}
	else
	{
		while (*env && ft_strncmp("PATH", *env, 4))
			env++;
		if (*env == NULL)
		{
			perror("ERROR finding PATH");
			// free_env();
			free_c_env(env);
			exit(EXIT_FAILURE);
		}
	}
	return (*env + 5);
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
	printf("%s: command not found\n", cmd);
	free_cmd_paths(cmd_paths);
	return (NULL);
}
