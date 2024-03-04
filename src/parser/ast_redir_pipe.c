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