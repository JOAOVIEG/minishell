/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_char_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:29:21 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/17 20:30:23 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	find_char_index(char *str, char c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (ptr)
		return (ptr - str);
	else
		return (-1);
}
