/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:06:14 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/11 19:06:47 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_to_history(t_shell *shell, char *command)
{
	t_history_entry	*new_entry;

	new_entry = ft_calloc(1, sizeof(t_history_entry));
	new_entry->command = ft_strdup(command);
	new_entry->next = shell->history;
	shell->history = new_entry;
}
