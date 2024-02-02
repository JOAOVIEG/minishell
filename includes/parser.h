/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:08:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/02 18:54:03 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_lst_tokens
{
	char				*data;
	struct s_lst_tokens	*next;
}						t_lst_tokens;

typedef struct s_parser
{
	t_lst_tokens		*tokens;

}						t_parser;

t_parser				*init_parser(void);
void					parse_to_list(t_lexer *lexer, t_parser *parser);
void					print_list(t_lst_tokens *head);

// free_parser
void					free_parser(t_parser *parser);

#endif