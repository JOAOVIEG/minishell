/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:31:08 by joaocard          #+#    #+#             */
/*   Updated: 2024/03/17 20:56:46 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (buffer)
		printf("%s\n", buffer);
	else
	{
		perror("getcwd");
		shell()->status = 1;
	}
	free(buffer);
	shell()->status = EXIT_SUCCESS;
}
