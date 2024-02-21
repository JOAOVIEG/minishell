/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:48:08 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/21 15:08:53 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_type(int type)
{
	if (type == TYPE_COMMAND)
		printf("TYPE_COMMAND\n");
	else if (type == TYPE_PIPE)
		printf("TYPE_PIPE\n");
	else if (type == TYPE_REDIRECT)
		printf("TYPE_REDIRECT\n");
	else if (type == TYPE_REDIRECT_IN)
		printf("TYPE_REDIRECT_IN\n");
	else if (type == TYPE_REDIRECT_OUT)
		printf("TYPE_REDIRECT_OUT\n");
	else if (type == TYPE_HEREDOC)
		printf("TYPE_HEREDOC\n");
	else if (type == TYPE_QUOTES)
		printf("TYPE_QUOTES\n");
	else if (type == TYPE_ENV_VAR)
		printf("TYPE_ENV_VAR\n");
	else if (type == TYPE_ARG)
		printf("TYPE_ARG\n");
	
}
void	print_tree(t_node *node, int depth, char *side)
{
	if (node == NULL)
		return ;
	for (int i = 0; i < depth; i++)
		printf("\t");
	printf("├──%s(", side);
	for (int i = 0; node->cmd->arg[i] != NULL; i++)
	{
		printf("%s ", node->cmd->arg[i]);
	}
	printf(") ");
	print_type(node->type);
	print_tree(node->left, depth + 1, "left");
	print_tree(node->right, depth + 1, "right");
}