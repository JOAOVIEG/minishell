/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:01:03 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/14 21:02:32 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	build_tree(t_shell *shell)
{
	if (shell->parser->pipe_count == 0 && shell->parser->redir_count == 0
		&& shell->parser->heredoc_count == 0)
		build_tree_simple_command(shell);
	else if (shell->parser->pipe_count > 0 && shell->parser->redir_count == 0
		&& shell->parser->heredoc_count == 0)
		build_pipe_tree(shell);
	else if (shell->parser->pipe_count == 0 && shell->parser->redir_count > 0
		&& shell->parser->heredoc_count == 0)
		build_redir_tree(shell);
	else if (shell->parser->pipe_count > 0 && shell->parser->redir_count > 0
		&& shell->parser->heredoc_count == 0)
		build_redir_pipe_tree(shell);
	else if (shell->parser->heredoc_count > 0 && shell->parser->pipe_count == 0
		&& shell->parser->redir_count == 0)
		build_heredoc_tree(shell);
	else if (shell->parser->heredoc_count > 0 && shell->parser->pipe_count > 0
		&& shell->parser->redir_count == 0)
		build_heredoc_pipe_tree(shell);
	else if (shell->parser->heredoc_count > 0 && shell->parser->pipe_count == 0
		&& shell->parser->redir_count > 0)
		build_heredoc_redir_tree(shell);
	else if (shell->parser->heredoc_count > 0 && shell->parser->pipe_count > 0
		&& shell->parser->redir_count > 0)
		build_heredoc_redir_tree(shell);
}
