/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:59:55 by wiferrei          #+#    #+#             */
/*   Updated: 2024/01/30 14:04:32 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum s_node_type
{
	NODE_PIPE = (1 << 0),
	NODE_REDIRECT_IN = (1 << 1),
	NODE_REDIRECT_OUT = (1 << 2),
	NODE_CMDPATH = (1 << 3),
	NODE_ARGUMENT = (1 << 4),

	NODE_DATA = (1 << 5),
}					t_node_type;

typedef struct s_astree
{
	t_node_type		type;
	char			*data;
	struct s_astree	*left;
	struct s_astree	*right;
}					t_astree;

typedef struct s_parser_buffer
{
	t_token			*left;
	t_token			*right;
}					t_parser_buffer;

typedef struct s_parser
{
	t_astree		*ast;
	int				nbr_pipes;
	int				nbr_redir_in;
	int				nbr_redir_out;
	t_parser_buffer	*buffer;
}					t_parser;

t_parser			*init_parser(void);
void				count_pipes_and_redirections(t_parser *parser,
						t_token *tokens);

// tree functions
t_astree			*ast_create_node(void *item, t_node_type type);
void				ast_free_node(t_astree *node);
// this function can't be void
void				build_ast(t_token *tokens, t_parser *parser);
t_node_type			get_token_type(t_token *token);
t_astree			*get_rightmost_node(t_astree *node);
int					ast_get_next_precedence(t_node_type op);

void	split_token_list(t_token *tokens, t_parser *parser, char *delimiter);


#endif