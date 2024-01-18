/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:22:51 by wiferrei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/18 13:41:07 by joaocard         ###   ########.fr       */
=======
/*   Updated: 2024/01/17 15:44:32 by wiferrei         ###   ########.fr       */
>>>>>>> 281550cd5d156162cfbeb31c181e38837bb70219
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/includes/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include  "lexer.h"

typedef struct s_env 
{
	char			*name;
	char			*value;
	struct s_env	*next;	
}	t_env;

typedef	struct s_minishell
{

}	t_minishell;

typedef struct s_shell
{
	t_env	*v_env;
	char	*line;
	bool	signal_set;
	//t_lexer_state lx_state;
}			t_shell;

#endif
