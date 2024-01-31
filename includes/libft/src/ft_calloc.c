/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:11:24 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/31 12:37:41 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	dest = malloc(nmemb * size);
	if (dest == NULL)
	{
		return (NULL);
	}
	ft_memset(dest, 0, nmemb * size);
	return (dest);
}
