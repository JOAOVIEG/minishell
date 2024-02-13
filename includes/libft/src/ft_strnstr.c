/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:54:53 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/13 14:32:06 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// char	*ft_strnstr(const char *str, const char *to_find, size_t n)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (to_find[0] == '\0')
// 	{
// 		return ((char *)str);
// 	}
// 	while (str[i] != '\0')
// 	{
// 		j = 0;
// 		while (str[i + j] == to_find[j] && str[i + j] != '\0' && i + j < n)
// 		{
// 			if (to_find[j + 1] == '\0')
// 			{
// 				return ((char *)(&str[i]));
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }
/*Joao uses his own because seems simplier. Hope you dont mind :)*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = ft_strlen((char *)little);
	if (*little == 0)
		return ((char *) big);
	if (len == 0)
		return (0);
	while (*(char *)big && (int)(len - i) != -1)
	{
		if (ft_strncmp((char *)big, (char *)little, i) == 0)
			return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}
