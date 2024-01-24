/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:59:55 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/24 17:46:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_btree
{
	void			*item;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

typedef struct s_parser
{
	t_btree			*ast;
}					t_parser;

t_parser			*init_parser(void);

// Btree functions

t_btree				*btree_create_node(void *item);
t_btree				*btree_build_ast(t_token *tokens);

#endif