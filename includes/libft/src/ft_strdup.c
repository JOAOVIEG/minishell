/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:48:32 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/23 15:31:11 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(char *src)
{
	char	*cpy;
	int		i;

	i = -1;
	if (src == NULL)
	{
		return (NULL);
	}
	cpy = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (cpy == NULL)
	{
		return (0);
	}
	while (src[++i])
	{
		cpy[i] = src[i];
	}
	cpy[i] = '\0';
	return (cpy);
}
