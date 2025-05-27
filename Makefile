NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include
LIBS = -lreadline

SRC_DIR = source
OBJ_DIR = build

SRC_FILES = main split ft_strncmp
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@ executable"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< into $@"
	@$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

valgrind: all
	valgrind ./minishell

clean:
	@echo "Deleting $(OBJ_DIR) directory"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Deleting $(NAME) executable"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)