// #include "../../includes/minishell.h"

// void	piped_try(t_node *node)
// {
// 	int		pipe_end[2];
// 	pid_t	left_pid;
// 	pid_t	right_pid;
// 	int		l_status;
// 	int		status;
// 	if (pipe(pipe_end) < 0)
// 	{
// 		perror("Error at pipe");
// 		exit_shell(EXIT_FAILURE);
// 	}
// 	left_pid = fork();
// 	if (left_pid < 0)
// 	{
// 		perror("left fork failed");
// 		exit_shell(2);
// 	}
// 	else if (left_pid == 0)
// 	{
// 		shell()->status = EXIT_SUCCESS;
// 		execute_left_node(node, pipe_end);
// 		close(pipe_end[0]);
// 		node->left->fd_out = pipe_end[1];
// 		dup2(node->left->fd_out, STDOUT_FILENO);
// 		ft_execute(node->left);
// 		close(node->left->fd_out);
// 		close(pipe_end[1]);
// 		exit_shell(shell()->status);
// 	}
// 	if (left_pid > 0)
// 	{
// 		waitpid(left_pid, &l_status, 0);
// 		if (WIFEXITED(l_status))
// 			shell()->status = WEXITSTATUS(l_status);
// 	}
// 	right_pid = fork();
// 	if (!node->fd_in)
// 		node->fd_in = dup(STDIN_FILENO);
// 	if (!node->fd_out)
// 		node->fd_out = dup(STDOUT_FILENO);
// 	if (right_pid < 0)
// 	{
// 		perror("right fork failed");
// 		exit_shell(EXIT_FAILURE);
// 	}
// 	else if (right_pid == 0)
// 	{
// 		shell()->status = EXIT_SUCCESS;
// 		if (node->fd_in)
// 			close(node->right->fd_in);
// 		node->right->fd_in = pipe_end[0];
// 		close(pipe_end[1]);
// 		dup2(node->right->fd_in, STDIN_FILENO);
// 		ft_execute(node->right);
// 		close(node->right->fd_in);
// 		close(pipe_end[0]);
// 		exit_shell(shell()->status);
// 	}
// 	else
// 	{
// 		close(pipe_end[0]);
// 		if (node->right->fd_in)
// 			close(node->right->fd_in);
// 		close(pipe_end[1]);
// 		if (node->left->fd_out)
// 			close(node->left->fd_out);
// 		waitpid(right_pid, &status, 0);
// 		if (WIFEXITED(status))
// 			shell()->status = WEXITSTATUS(status);
// 	}
// }
// void	ft_exec_piped(t_node *node)
// {	
// 	int		pipe_end[2];
// 	pid_t	left_pid;
// 	pid_t	right_pid;
// 	int		l_status;

// 	if (pipe(pipe_end) < 0)
// 	{
// 		perror("Error at pipe");
// 		exit_shell(EXIT_FAILURE);
// 	}
// 	left_pid = fork();
// 	left_node_process(node, pipe_end, left_pid);
// 	if (left_pid > 0)
// 	{
// 		waitpid(left_pid, &l_status, 0);
// 		if (WIFEXITED(l_status))
// 			shell()->status = WEXITSTATUS(l_status);
// 	}
// 	right_pid = fork();
// 	assign_fds(node->right);
// 	right_node_process(node, pipe_end, right_pid);
// 	parent_pipe_exec_control(node, pipe_end, right_pid);
// }