NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Iincludes/libft/includes

INC_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
		
SRC := $(addprefix $(SRC_DIR)/, \
    minishell.c \
	main_utilis.c \
    clean_tree.c \
    end_shell.c \
) \
$(addprefix $(SRC_DIR)/lexer/, \
    create_token.c \
    free_lexer.c \
    lexer.c \
    process_tokens.c \
    process_tokens_utils.c \
    split_into_tokens.c \
) \
$(addprefix $(SRC_DIR)/parser/, \
    add_to_history.c \
    ast.c \
    buffer_utils.c \
    build_ast_heredoc.c \
    build_ast_piped_cmd.c \
    build_ast_redir_cmd.c \
    build_ast_simple_cmd.c \
    build_ast_utils_00.c \
    build_ast_utils_01.c \
    build_ast_utils_02.c \
    expancion.c \
    expancion_utils.c \
    expansion_hd.c \
    free_parser.c \
    get_token_type.c \
    grammar.c \
    grammar_env_var.c \
    grammar_here_document.c \
    grammar_quotes.c \
    grammar_redirection.c \
    grammar_utils.c.c \
    handle_signals.c \
    lst_tokens_utils.c \
    parser.c \
    parse_to_list.c \
    print_tree.c \
    process_quotes.c \
    handle_tilde.c \
) \
$(addprefix $(SRC_DIR)/execute/built_ins/, \
    cd.c \
    echo.c \
    env.c \
    exit.c \
    export_actions.c \
    export_actions_utils.c \
    export_buffer.c \
    export.c \
    export_grammar.c \
    export_utilis.c \
    pwd.c \
    unset.c \
) \
$(addprefix $(SRC_DIR)/execute/env/, \
    env_init.c \
) \
$(addprefix $(SRC_DIR)/execute/, \
    exec_builtin1.c \
    exec_builtin.c \
    exec_cmd.c \
    exec_cmd_utilis.c \
    free_utilis.c \
    ft_exec_piped.c \
    ft_execute.c \
    ft_utilis1.c \
    ft_utilis2.c \
    ft_utilis.c \
    heredoc.c \
	heredoc_piped.c \
	heredoc_piped_utilis.c \
    redirections1.c \
    redirections.c \
    simple_cmds_utilis.c \
)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_DIR = ./includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline
	@echo "minishell compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@echo "minishell object files removed"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@echo "minishell removed"

re: fclean all

valgrind: re $(NAME)
	@cat readline.supp  >  /dev/null
	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes   ./$(NAME)

run: re
	@./$(NAME)

v: re
	valgrind --suppressions=readline.supp --track-fds=yes --trace-children=yes ./$(NAME)
#	 --trace-children=yes --track-origins=yes
# @./$(NAME) | cat -e

.PHONY: all clean fclean re v valgrind
