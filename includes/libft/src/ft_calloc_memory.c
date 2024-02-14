/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:29:23 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/14 16:33:30 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc_memory(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		perror("Error: Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	return (ptr);
}
