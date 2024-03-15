/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:20:55 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/15 07:20:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// int	ft_strncmp(const char *s1, char *s2, size_t n)
// {
// 	while (*s1 != '\0' && *s1 == *s2 && n > 0)
// 	{
// 		s1++;
// 		s2++;
// 		n--;
// 	}
// 	if (n == 0)
// 	{
// 		return (0);
// 	}
// 	return (*(unsigned char *)s1 - *(unsigned char *)s2);
// }

int	ft_strncmp(const char *sn1, const char *sn2, size_t nb)
{
	size_t	i;

	i = 0;
	while (i++ < nb && (*sn1 || *sn2))
	{
		if ((unsigned char)*sn1 != (unsigned char)*sn2)
			return ((unsigned char)*sn1 - (unsigned char)*sn2);
		sn1++;
		sn2++;
	}
	return (0);
}
