/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:52:07 by wiferrei          #+#    #+#             */
/*   Updated: 2024/04/04 15:09:28 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

// static int	ft_word_count(char *str, char charset)
// {
// 	int	i;
// 	int	word_count;

// 	word_count = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == charset)
// 			i++;
// 		if (str[i] != '\0')
// 			word_count++;
// 		while (str[i] != '\0' && str[i] != charset)
// 			i++;
// 	}
// 	return (word_count);
// }

// static int	ft_wordlen(char *str, char charset)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0' && str[i] != charset)
// 		i++;
// 	return (i);
// }

// static char	*ft_word(char *str, char charset)
// {
// 	int		len_word;
// 	int		i;
// 	char	*word;

// 	i = 0;
// 	len_word = ft_wordlen(str, charset);
// 	word = (char *)malloc(sizeof(char) * (len_word + 1));
// 	while (i < len_word)
// 	{
// 		word[i] = str[i];
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**strings;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	strings = (char **)malloc(sizeof(char *) * (ft_word_count((char *)s, c)
// 				+ 1));
// 	if (!s || !strings)
// 		return (0);
// 	while (s[j] != '\0')
// 	{
// 		while (s[j] != '\0' && s[j] == c)
// 			j++;
// 		if (s[j] != '\0')
// 		{
// 			strings[i] = ft_word((char *)&s[j], c);
// 			free()
// 			i++;
// 		}
// 		while (s[j] != '\0' && s[j] != c)
// 			j++;
// 	}
// 	strings[i] = 0;
// 	return (strings);
// }
static int	index_count(char const *s, char c)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			index++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (index);
}

static int	word_len(char const *s, char c, int i)
{
	while (*(s + i) && *(s + i) != c)
	{
		i++;
	}
	return (i);
}

static void	get_array_elements(char **array, char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = word_len(s, c, i);
			*array = ft_calloc(sizeof(**array), len - i + 1);
			if (!*array)
				return ;
			ft_memcpy(*array, s + i, len - i);
			array++;
			i = len - 1;
		}
		i++;
	}
	return ;
}

static char	**free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (NULL);
	while (*(array + i))
	{
		free(*(array + i));
		*(array + i) = NULL;
		i++;
	}
	free (array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s || s == NULL)
		return (NULL);
	array = ft_calloc(sizeof(*array), index_count(s, c) + 1);
	if (!array)
		return (NULL);
	get_array_elements(array, s, c);
	if (!array)
		return (free_array(array));
	return (array);
}
