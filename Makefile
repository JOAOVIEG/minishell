NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes -Iincludes/libft/includes

INC_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
		
SRC = $(wildcard $(SRC_DIR)/*.c) \
      $(wildcard $(SRC_DIR)/lexer/*.c) \
      $(wildcard $(SRC_DIR)/parser/*.c) \
      $(wildcard $(SRC_DIR)/execute/built_ins/*.c) \
      $(wildcard $(SRC_DIR)/execute/env/*.c) \
	  $(wildcard $(SRC_DIR)/execute/*.c)

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

.PHONY: all clean fclean re valgrind
run: re
	@./$(NAME)

v: re
	valgrind --suppressions=readline.supp --track-fds=yes --trace-children=yes ./$(NAME)
#	 --trace-children=yes --track-origins=yes
# @./$(NAME) | cat -e

.PHONY: all clean fclean re v
