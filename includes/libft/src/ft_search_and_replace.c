/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_and_replace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:54:50 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/26 14:56:12 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_search_and_replace(const char *str, const char *srch,
		const char *rplc)
{
	char	*new_str;
	char	*ptr;
	char	*tmp;
	int		srch_len;

	new_str = ft_strdup((char *)str);
	srch_len = ft_strlen(srch);
	ptr = ft_strstr(new_str, srch);
	while (ptr)
	{
		tmp = new_str;
		*ptr = '\0';
		new_str = ft_strjoin(new_str, rplc);
		new_str = ft_strjoin(new_str, ptr + srch_len);
		free(tmp);
		ptr = ft_strstr(new_str, srch);
	}
	return (new_str);
}
