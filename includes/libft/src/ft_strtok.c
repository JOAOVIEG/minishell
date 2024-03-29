/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:05:27 by wiferrei          #+#    #+#             */
/*   Updated: 2024/03/29 19:58:48 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next_token;
	char		*token;
	int			i;

	if (str)
		next_token = str;
	token = next_token;
	if (!token)
		return (NULL);
	i = 0;
	while (next_token[i])
	{
		if (ft_strstr(next_token + i, delim) == next_token + i)
		{
			next_token[i] = '\0';
			next_token = next_token + i + ft_strlen(delim);
			return (token);
		}
		i++;
	}
	next_token = NULL;
	return (token);
}
