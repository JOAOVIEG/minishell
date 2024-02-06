/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/02/06 14:47:55 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/builtins.h"
# include "../../includes/lexer.h"
# include "../../includes/parser.h"

void ft_simple_cmds()
{	
	/*if is a bultin executes builtin.
	else, ecxecutes form path*/
	if (is_builtin())
		exec_builtin();
	else
		exec_cmd();
}


int	is_builtin()
{
	char *cmd;

	cmd = shell()->node->arg[0];
	if (ft_strcmp(cmd, "cd") == 0 || \\
			ft_strcmp(cmd, "pwd") == 0 || \\
			ft_strcmp(cmd, "echo") == 0 || \\
			ft_strcmp(cmd, "export") == 0 || \\
			ft_strcmp(cmd, "unset") == 0 || \\
			ft_strcmp(cmd, "env") == 0 || \\
			ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	exec_cmd()
{
	char *cmd;
	char	**args;
	char	**env;
	pid_t	pid;
	
	cmd = shell()->node->arg[0];
	
}

void exec_builtin()
{
	char **cmd;

	cmd = shell()->node->arg;
	if (ft_strcmp(cmd[0], "cd") == 0)
		cd (cmd[1]);
	if (ft_strcmp(current->value, "pwd") == 0)
		pwd();
	if (ft_strcmp(cmd[0], "echo") == 0)
		echo(cmd);
	if (ft_strcmp(cmd[0], "export") == 0)
		export(cmd);
	if (ft_strcmp(cmd[0], "exit") == 0)
		exit(cmd);
	if (ft_strcmp(cmd[0], "unset") == 0)
		unset(cmd);
	if (ft_strcmp(cmd[0], "env") == 0)
		env();
}

void	ft_execute(void)
{
	/*if node is of type cmd*/
	ft_simple_cmds();

}
