NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
#CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
INCLUDE = -I./include -I./include/exec -I./include/parser \
	-I./include/exec/redirects -I./include/exec/builtsin \
	-I./include/exec/builtsin/parent -I./include/exec/builtsin/child \
	-I./include/parser/commands -I./include/parser/tokens \
	-I./include/env -I./libft/include
#INCLUDE = -I./include -I./libft/include -lft -fsanitize=address
LIBS = -lreadline -L./libft -lft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = source
OBJ_DIR = build

EXEC_FILES = exec/exec exec/exec_utils exec/print_error \
	exec/redirects/here_doc exec/redirects/here_doc_utils \
	exec/redirects/set_dup2 exec/redirects/set_dup2_utils \
	exec/redirects/pipes

BUILTSIN = exec/builtsin/builtsin  \
	exec/builtsin/parent/cd exec/builtsin/parent/exit \
	exec/builtsin/parent/export exec/builtsin/parent/unset \
	exec/builtsin/child/echo exec/builtsin/child/env \
	exec/builtsin/child/pwd

PARSER_FILES = parser/parse_read_line parser/alloc \
	parser/access_program parser/access \
	parser/parse_error \
	parser/tokens/token \
	parser/tokens/token_list parser/tokens/token_operator \
	parser/tokens/token_string parser/tokens/token_utils \
	parser/tokens/token_expand parser/tokens/token_free \
	parser/commands/commands parser/commands/commands_args \
	parser/commands/commands_list parser/commands/commands_redirect \
	parser/commands/commands_redirect_utils \

ENV_FILES = env/envp env/envp_utils

MAIN_FILES = main utils free free_utils signals

ALL_SRC_FILES = $(MAIN_FILES) $(EXEC_FILES) $(PARSER_FILES) $(ENV_FILES) $(BUILTSIN)

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(ALL_SRC_FILES)))
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
	@mkdir -p $(dir $@)
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