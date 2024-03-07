// #include "../../includes/minishell.h"

// t_node	*create_node_and_update_pipe_redir_tree(t_node **tree_root,
//         t_node **rightmost_node, t_lst_tokens **cmd_tokens, t_lst_tokens **current)
// {
//     t_node	*new_node;
//     t_lst_tokens *redir_tokens = NULL;

//     // Extract redirection tokens
//     while (*current && (*current)->type == TYPE_REDIRECT)
//     {
//         redir_tokens = get_cmd_tokens(current);
//         *current = (*current)->next;
//     }

//     new_node = new_tree_node(*cmd_tokens);  // Dereference cmd_tokens here
//     if (!new_node)
//         return (NULL);

//     // Store redirection tokens in new_node->cmd->file
//     new_node->cmd->file = redir_tokens;

//     if (!*tree_root)
//     {
//         *tree_root = new_node;
//         *rightmost_node = new_node;
//     }
//     else
//         update_tree_root(tree_root, rightmost_node,
//             create_pipe_node(*rightmost_node, new_node));
//     return (new_node);
// }

// void	build_redir_pipe_tree(t_shell *shell)
// {
//     t_node *tree_root;
//     t_node *rightmost_node;
//     t_lst_tokens *current;
//     t_lst_tokens *cmd_tokens;

//     tree_root = NULL;
//     rightmost_node = NULL;
//     current = shell->parser->tokens;
//     while (current != NULL)
//     {
//         cmd_tokens = get_cmd_tokens(&current);
//         if (!cmd_tokens)
//             return ;
//         if (!create_node_and_update_pipe_redir_tree(&tree_root, &rightmost_node,
//                 &cmd_tokens, &current))
//             return ;
//         if (current && current->type == TYPE_PIPE)
//             current = current->next;
//     }

//     shell->node = tree_root;
// }



// void	build_redir_pipe_tree(t_shell *shell)
// {
// 	t_node			*tree_root;
// 	t_token_queue	cmds;
// 	t_token_queue	redir_files;
// 	t_lst_tokens	*current;

// 	tree_root = NULL;
// 	cmds.head = NULL;
// 	cmds.tail = NULL;
// 	redir_files.head = NULL;
// 	redir_files.tail = NULL;
// 	current = shell->parser->tokens;
// 	while (current != NULL)
// 	{
// 		while (current != NULL && current->type != TYPE_PIPE)
// 		{
// 			if (current->type == TYPE_REDIRECT)
// 				redir_files.head = get_redir_list(&current, &redir_files.head,
// 						&redir_files.tail);
// 			else
// 				cmds.head = get_cmd_list(&current, &cmds.head, &cmds.tail);
// 		}
// 		if (tree_root == NULL)
// 		{
// 			tree_root = create_pipe_node(new_redir_tree_node(cmds, redir_files),
// 					NULL);
// 		}
// 		else
// 		{
// 			tree_root->right = new_redir_tree_node(cmds, redir_files);
// 		}
// 		if (current != NULL)
// 			current = current->next;
// 		free_lst_tokens(cmds.head);
// 		free_lst_tokens(redir_files.head);
// 		cmds.head = NULL;
// 		cmds.tail = NULL;
// 		redir_files.head = NULL;
// 		redir_files.tail = NULL;
// 	}
// 	shell->node = tree_root;
// }

// void	make_env_var(t_shell *shell)
// {
// 	t_lst_tokens	*current;
// 	t_lst_tokens	*head;
// 	t_env			*env;
// 	t_env			*current_env;
// 	char			*value;
// 	char			*trimmed;

// 	// char			*start;
// 	// char			*end;
// 	// char			*substring;
// 	head = shell->parser->tokens;
// 	current = head;
// 	env = shell->v_env;
// 	current_env = env;
// 	while (current)
// 	{
// 		if (current->type == TYPE_ENV_VAR)
// 		{
// 			trimmed = ft_strtrim(current->data, "$");
// 			free(current->data);
// 			current->data = NULL;
// 			current->data = ft_strdup(trimmed);
// 			free(trimmed);
// 			while (current_env)
// 			{
// 				if (ft_strncmp(current->data, current_env->name,
// 						ft_strlen(current_env->name)) == 0)
// 				{
// 					value = ft_strdup(current_env->value);
// 					free(current->data);
// 					current->data = value;
// 				}
// 				current_env = current_env->next;
// 			}
// 			current_env = env;
// 		}
// 		if (current->type == TYPE_ARG || current->type == TYPE_COMMAND)
// 		{
// 			if (ft_strchr(current->data, '$'))
// 			{
// 				// start = ft_strchr(current->data, '$');
// 				// end = strpbrk(start, " \t\n\0"); /* define my own function */
// 				// if (!end)
// 				// 	end = start + ft_strlen(start);
// 				// substring = ft_strndup(start, end - start);
// 				// trimmed = ft_strdup(ft_strtrim(substring, "$"));
// 				// printf("Substring: %s\n", substring);
// 				// printf("Trimmed: %s\n", trimmed);
// 				// free(substring);
// 				replace_with_env_var(&current, current_env);
// 				printf("ATTENTION: I NEED TO IMPLEMENT THIS CASE\n");
// 			}
// 		}
// 		current = current->next;
// 	}
// 	shell->parser->tokens = head;
// } 
