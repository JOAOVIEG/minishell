/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:59:55 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/29 16:54:42 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum s_astree_type
{
	NODE_CMDLINE,
	NODE_BCKGRND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_CMDPATH,
	NODE_ARGUMENT

}					t_astree_type;

typedef struct s_astree
{
	void			*item;
	t_astree_type	type;
	struct s_astree	*left;
	struct s_astree	*right;
}					t_astree;

typedef struct s_parser
{
	t_astree		*ast;
}					t_parser;

t_parser			*init_parser(void);

// tree functions
t_astree			*ast_create_node(void *item, t_astree_type type);
void				ast_free_node(t_astree *node);
t_astree			*build_ast(t_token *tokens);
t_astree_type		get_token_type(t_token *token);
t_astree			*get_rightmost_node(t_astree *node);

#endif