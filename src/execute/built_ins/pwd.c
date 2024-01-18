/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:57 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/18 10:05:16 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd(void)
{
	char	*buffer;
	
	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		printf("%s\n", buffer);
		free(buffer);
	}
	else
	{
		perror("error\n");
		/*shell exit status set to 1*/
	}
	/*shell exit status set to 0*/
}