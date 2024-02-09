/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/09 16:29:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include "../../includes/lexer.h"
// # include "../../includes/parser.h"
# include "../../includes/minishell.h"

void ft_simple_cmds(t_node *node)
{	
	/*if is a bultin executes builtin.
	else, ecxecutes form path*/
	if (is_builtin(node))
		exec_builtin(node);
	else
		exec_cmd(node);
}


int	is_builtin(t_node *node)
{
	char *cmd;

	cmd = node->cmd->arg[0];
	if (ft_strcmp(cmd, "cd") == 0 || \
			ft_strcmp(cmd, "pwd") == 0 || \
			ft_strcmp(cmd, "echo") == 0 || \
			ft_strcmp(cmd, "export") == 0 || \
			ft_strcmp(cmd, "unset") == 0 || \
			ft_strcmp(cmd, "env") == 0 || \
			ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	exec_builtin(t_node *node)
{
	char **cmd;

	cmd = node->cmd->arg;
	if (ft_strcmp(cmd[0], "cd") == 0)
		cd (cmd[1]);
	if (ft_strcmp(cmd[0], "pwd") == 0)
		pwd();
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo(cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		export(cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit_shell(cmd);
	if (ft_strcmp(cmd[0], "unset") == 0)
		unset(cmd);
	if (ft_strcmp(cmd[0], "env") == 0)
		env();
}

void	exec_cmd(t_node *node)
{
	char	**env;
	int		status;
	pid_t	pid;
	
	env = env_list_to_arr();
	check_path(env);
	pid = fork();
	if (pid < 0)
	{
		perror("Error forking");
		free_env();
		free_c_env(env);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if ((shell()->node->cmd->valid_cmd_path = get_cmd(shell()->node->cmd->cmd_path, \
				shell()->node->cmd->arg[0])) == NULL)
		{
			free_env();
			free_c_env(env);
			exit(EXIT_FAILURE);
		}
		redirections(node->fd_in, node->fd_out);
		if (execve(shell()->node->cmd->valid_cmd_path, shell()->node->cmd->arg, env) < 0)
		{
			free_env();
			free_c_env(env);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close_fds(node->fd_in, node->fd_out);
		waitpid(pid, &status, 0);
		free_env();
		free_c_env(env);
	}
}

void	close_fds(int fd_i, int fd_o)
{
	if (fd_i != STDIN_FILENO)
		close(fd_i);
	if (fd_o != STDOUT_FILENO)
		close(fd_o);
}

int	redirections(int fd_i, int fd_o)
{
	if (redirect_in(fd_i) == -1 || redirect_out(fd_o) == -1)
		return (-1);
	return (0);
}

int	redirect_in(int fd_i)
{
	int red_i;
	
	if (fd_i == STDIN_FILENO)
		return (STDIN_FILENO);
	else
	{
		if ((red_i = dup2(fd_i, STDIN_FILENO)) < 0)
			return (-1);
		close(fd_i);
	}
	return (red_i);
}

int	redirect_out(int fd_o)
{
	int red_o;
	
	if (fd_o == STDOUT_FILENO)
		return (STDOUT_FILENO);
	else
	{
		if ((red_o = dup2(fd_o, STDOUT_FILENO)) < 0)
			return (-1);
		close(fd_o);
	}
	return (red_o);
}

void	free_c_env(char **env)
{
	int i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	env = NULL;
}

char	**env_list_to_arr()
{
	int		count;
	int		i;
	t_env	*current;
	char	**envp;
	char *tmp;

	count = 0;
	i = 0;
	current = shell()->v_env;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		perror("malloc envp");
		exit(EXIT_FAILURE);
	}
	current = shell()->v_env;
	while ( i < count)
	{
		tmp = ft_strjoin(current->name, "=");
		envp[i] = ft_strjoin(tmp, current->value);
		if (!envp[i])
		{
			perror("malloc envp[i]");
			free_env();
			free_c_env(envp);
			exit(EXIT_FAILURE);
		}
		free(tmp);
		i++;
		current = current->next;
	}
	tmp = NULL;
	envp[i] = NULL;
	return (envp);
}

void	check_path(char **env)
{
	shell()->node->cmd->path = get_path(env);
	if (shell()->node->cmd->path)
		shell()->node->cmd->cmd_path = ft_split(shell()->node->cmd->path, \
			':');
}

char	*get_path(char **env)
{
	if (*env == NULL)
	{
		perror("ERROR env at path");
		free_env();
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
			free_env();
			free_c_env(env);
			exit(EXIT_FAILURE);
		}
	}
	return (*env + 5);
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
	return (NULL);
}

void	ft_execute(t_node *node)
{
	/*Initializing the new variables fd_in and out for the
	simpliest case: one node cmd. Already taking into account pipe
	and other cases than simple commands*/
	shell()->node->fd_in = dup(STDIN_FILENO);
	shell()->node->fd_out = dup(STDOUT_FILENO);
	/*if node is of type cmd*/
	ft_simple_cmds(node);
}
