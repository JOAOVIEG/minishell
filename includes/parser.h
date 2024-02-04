/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:08:02 by wiferrei          #+#    #+#             */
/*   Updated: 2024/02/04 17:41:35 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_token_type
{
	TYPE_PIPE,
	TYPE_COMMAND,
	TYPE_ARG,
	TYPE_REDIRECT,
	TYPE_HEREDOC,
	TYPE_QUOTES,
	TYPE_ENV_VAR
}						t_token_type;

typedef struct s_lst_tokens
{
	char				*data;
	t_token_type		type;
	struct s_lst_tokens	*next;
}						t_lst_tokens;

typedef struct s_parser
{
	t_lst_tokens		*tokens;

}						t_parser;

t_parser				*init_parser(void);

void					parse_to_list(t_lexer *lexer, t_parser *parser);

void					define_type(t_lst_tokens *current, t_lst_tokens *prev);
void					get_token_type(t_lst_tokens *tokens);

void					print_list(t_lst_tokens *head);

// free_parser
void					free_parser(t_parser *parser);

#endif
