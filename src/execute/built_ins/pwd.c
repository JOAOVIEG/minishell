/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:31:08 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/30 14:52:57 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

void	pwd(void)
{
	char	*buffer;
	
	buffer = getcwd(NULL, 0);
	if (buffer)
		printf("%s\n", buffer);
	else
	{
		// printf("minishell: %s\n", strerror(errno));
		perror("getcwd");
		shell()->status = 1;
	}
	free(buffer);
	shell()->status = 0;
}
