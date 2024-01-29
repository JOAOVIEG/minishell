/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:12:59 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 17:05:37 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_astree_type	get_token_type(t_token *token)
{
    if (token->value[0] == CHAR_PIPE)
        return (NODE_PIPE);
    else if (token->value[0] == CHAR_AMPERSAND)
        return (NODE_BCKGRND);
    else if (token->value[0] == CHAR_LESSER)
        return (NODE_REDIRECT_IN);
    else if (token->value[0] == CHAR_GREATER)
        return (NODE_REDIRECT_OUT);
    else
        return (NODE_CMDLINE);
}
