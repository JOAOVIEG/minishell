/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:47:27 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/01 11:10:38 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	count = 0;
	while (s1[count] == s2[count] && s1[count] != '\0')
	{
		count++;
	}
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}
// int	ft_strcmp(const char *sc1, const char *sc2)
// {
// 	while (*sc1 || *sc2)
// 	{
// 		if ((unsigned char)*sc1 != (unsigned char)*sc2)
// 			return ((unsigned char)*sc1 - (unsigned char)*sc2);
// 		sc1++;
// 		sc2++;
// 	}
// 	return (0);
// }