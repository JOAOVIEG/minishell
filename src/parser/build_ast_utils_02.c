/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_utils_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:23:16 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 20:56:05 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_back(t_lst_tokens **current, t_lst_tokens **cmd_tokens,
		t_lst_tokens **tail)
{
	t_lst_tokens	*new_token;

	new_token = ft_calloc_memory(1, sizeof(t_lst_tokens));
	new_token->data = ft_strdup((*current)->data);
	new_token->type = (*current)->type;
	new_token->next = NULL;
	lst_tokenadd_back(cmd_tokens, tail, new_token);
	*current = (*current)->next;
}

t_lst_tokens	*get_redir_list(t_lst_tokens **current,
		t_lst_tokens **cmd_tokens, t_lst_tokens **tail)
{
	add_token_back(current, cmd_tokens, tail);
	if (*current != NULL)
	{
		add_token_back(current, cmd_tokens, tail);
	}
	return (*cmd_tokens);
}

void	build_token_queue(t_lst_tokens **current, t_buffer *buffer)
{
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		if ((*current)->type == TYPE_HEREDOC)
			buffer->heredocs.head = get_redir_list(current,
					&buffer->heredocs.head, &buffer->heredocs.tail);
		else if ((*current)->type == TYPE_REDIRECT)
			buffer->redir_files.head = get_redir_list(current,
					&buffer->redir_files.head, &buffer->redir_files.tail);
		else
			buffer->cmds.head = get_cmd_list(current, &buffer->cmds.head,
					&buffer->cmds.tail);
	}
}

void	build_heredoc_redir_queue(t_lst_tokens **current, t_token_queue *cmds,
		t_token_queue *heredocs, t_token_queue *redir_files)
{
	while (*current != NULL && (*current)->type != TYPE_PIPE)
	{
		if ((*current)->type == TYPE_HEREDOC)
			heredocs->head = get_redir_list(current, &heredocs->head,
					&heredocs->tail);
		else if ((*current)->type == TYPE_REDIRECT)
			redir_files->head = get_redir_list(current, &redir_files->head,
					&redir_files->tail);
		else
			cmds->head = get_cmd_list(current, &cmds->head, &cmds->tail);
	}
}
