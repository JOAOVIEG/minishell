/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:43:55 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/15 07:23:24 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new;
	size_t	i;

	len = 0;
	i = 0;
	while (len < n && s[len])
		len++;
	new = malloc(len + 1);
	if (new == NULL)
		return (NULL);
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
