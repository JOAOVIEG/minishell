/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:22:19 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/26 13:13:26 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_search_and_replace(const char *str, const char *srch,
		const char *rplc)
{
	char	*new_str;
	char	*ptr;
	char	*tmp;
	int		srch_len;

	new_str = ft_strdup((char *)str);
	srch_len = ft_strlen(srch);
	while ((ptr = ft_strstr(new_str, srch)))
	{
		tmp = new_str;
		*ptr = '\0';
		new_str = ft_strjoin(new_str, rplc);
		new_str = ft_strjoin(new_str, ptr + srch_len);
		free(tmp);
	}
	return (new_str);
}

void	process_current(t_lst_tokens *current, t_shell *shell)
{
	char	*new_data;

	if (current->type == TYPE_ENV_VAR && ft_strchr(current->data, '~'))
	{
		if (ft_strcmp(current->data, "~") == 0)
		{
			free(current->data);
			current->data = ft_strdup("$HOME");
		}
		else if (ft_strstr(current->data, "~/"))
		{
			new_data = ft_search_and_replace(current->data, "~",
					find_env_value(shell->v_env, "HOME"));
			free(current->data);
			current->data = new_data;
		}
	}
}

void	handle_tilde(t_shell *shell)
{
	t_lst_tokens	*current;
	t_lst_tokens	*head;

	head = shell->parser->tokens;
	current = head;
	while (current)
	{
		process_current(current, shell);
		current = current->next;
	}
	shell->parser->tokens = head;
}
