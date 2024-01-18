/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:43:55 by joaocard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/18 15:50:48 by joaocard         ###   ########.fr       */
=======
/*   Updated: 2024/01/18 15:50:25 by wiferrei         ###   ########.fr       */
>>>>>>> 34ab0d7 (changed structure)
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
