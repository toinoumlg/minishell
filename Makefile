NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
INCLUDE = -I./include -I./libft/include
#INCLUDE = -I./include -I./libft/include -lft -fsanitize=address
LIBS = -lreadline -L./libft -lft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = source
OBJ_DIR = build

SRC_FILES = main set_env parse_read_line utils \
	token token_list token_utils token_operator token_string token_check token_free \
	commands commands_args commands_redirect commands_list \
	access alloc \
	builtsin_child builtsin_parent \
	exec set_files_fds pipes exec_utils\
	free free_utils print_error

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@ executable"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT):
	@echo "Building libft"
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< into $@"
	@$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

valgrind: all
	valgrind --leak-check=full --trace-children=yes --track-fds=yes ./minishell

clean:
	@echo "Deleting $(OBJ_DIR) directory"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Deleting $(NAME) executable"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)