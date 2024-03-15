/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_piped1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:04:49 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/15 16:52:57 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_redir(t_node *node)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!node || !node->cmd || node->cmd->heredoc == NULL)
		return (0);
	while (node->cmd->heredoc && node->cmd->heredoc[i])
	{
		if (ft_strncmp(node->cmd->heredoc[i], "<<", 2) == 0)
		{
			j++;
		}
		i++;
	}
	return (j);
}