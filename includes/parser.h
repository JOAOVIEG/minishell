/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaocard <joaocard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:59:55 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/31 11:34:35 by joaocard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum s_node_type
{
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_DATA,
}					t_node_type;

typedef struct s_astree
{
	t_node_type		type;
	char			*data;
	struct s_astree	*left;
	struct s_astree	*right;
}					t_astree;

typedef struct s_parser
{
	t_astree		*ast;
}					t_parser;

t_parser			*init_parser(void);

// tree functions
t_astree			*ast_create_node(void *item, t_node_type type);
void				ast_free_node(t_astree *node);
t_astree			*build_ast(t_token *tokens);
t_node_type			get_token_type(t_token *token);
t_astree			*get_rightmost_node(t_astree *node);
int					ast_get_next_precedence(t_token_type op);

#endif