NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include -I./libft/include
LIBS = -lreadline -L./libft -lft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = source
OBJ_DIR = build

EXEC_FILES = exec/exec exec/exec_utils \
	exec/print_error exec/underscore \

BUILTSIN = builtsin/builtsin  \
	builtsin/parent/cd builtsin/parent/exit \
	builtsin/parent/export builtsin/parent/export_sorted \
	builtsin/parent/unset \
	builtsin/child/echo builtsin/child/env \
	builtsin/child/pwd builtsin/parent/update_pwd

REDIRECT = redirects/here_doc redirects/here_doc_expand \
	redirects/set_dup2 redirects/set_dup2_utils \
	redirects/pipes redirects/create_files \
	redirects/fd_utils

PARSER_FILES = parser/parse_read_line parser/alloc \
	parser/pre_parsing \
	parser/tokens/token parser/tokens/merge \
	parser/tokens/list parser/tokens/operator \
	parser/tokens/string parser/tokens/utils \
	parser/tokens/expand parser/tokens/remove \
	parser/tokens/expand_string \
	parser/commands/commands parser/commands/args \
	parser/commands/access_program parser/commands/access_redirects \
	parser/commands/redirect \

ENV_FILES = env/envp env/utils

MAIN_FILES = main free free_utils signals signals_heredoc

ALL_SRC_FILES = $(MAIN_FILES) $(EXEC_FILES) $(PARSER_FILES) $(ENV_FILES) $(BUILTSIN) $(REDIRECT)

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(ALL_SRC_FILES)))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $@ executable"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(LIBFT): force
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

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

force:

re: fclean all

.PHONY: all clean fclean re norme valgrind force

-include $(DEP)