/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:06:20 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/17 14:59:13 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"


t_lexer_state init_lexer_state(char *input)
{
    t_lexer_state state;
    state.input = input;
    state.current_position = 0;
    return state;
}