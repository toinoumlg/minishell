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

EXEC_FILES = exec/exec exec/exec_utils exec/print_error \
	

BUILTSIN = builtsin/builtsin  \
	builtsin/parent/cd builtsin/parent/exit \
	builtsin/parent/export builtsin/parent/unset \
	builtsin/child/echo builtsin/child/env \
	builtsin/child/pwd builtsin/parent/cd_update

REDIRECT = redirects/here_doc redirects/here_doc_expand \
	redirects/set_dup2 redirects/set_dup2_utils \
	redirects/pipes redirects/create_files

PARSER_FILES = parser/parse_read_line parser/alloc \
	parser/access_program parser/access \
	parser/pre_parsing \
	parser/tokens/token parser/tokens/merge \
	parser/tokens/list parser/tokens/operator \
	parser/tokens/string parser/tokens/utils \
	parser/tokens/expand parser/tokens/free \
	parser/tokens/expand_string \
	parser/commands/commands parser/commands/args \
	parser/commands/redirect \

ENV_FILES = env/envp env/utils

MAIN_FILES = main free free_utils signals

ALL_SRC_FILES = $(MAIN_FILES) $(EXEC_FILES) $(PARSER_FILES) $(ENV_FILES) $(BUILTSIN) $(REDIRECT)

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

norme:
	@norminette source include

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
