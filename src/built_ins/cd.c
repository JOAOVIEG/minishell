/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:02:27 by joaocard          #+#    #+#             */
/*   Updated: 2024/01/17 15:03:21 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*TODO*/
void	cd(char *path)
{
	if (!path)
	{
		/*In case there is no path, cd changes to HOME directory*/
		
	}
	else
	{
		if (chdir(path) == -1)
		{
			/*Error handling. It has to be exactly as bash shell message*/
		}
		/*If the directory change is successful, cd sets the value of the PWD environment
		variable to the new directory name, and sets the OLDPWD environment variable
		to the value of the current working directory before the change.
		The return status is zero if the directory is successfully changed, non-zero oth-
		erwise.*/
		
	}
}