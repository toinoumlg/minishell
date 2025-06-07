NAME = libft.a
CFLAGS = -Werror -Wall -Wextra
CC = cc
INCLUDE = -I./include

SRC_DIR = source
OBJ_DIR = build

SRC_FILES = strlen strlcpy strlcat memcmp atoi \
		strncmp toupper tolower isprint isdigit \
		isascii isalpha isalnum substr strchr \
		strrchr strnstr strjoin strtrim split \
		strdup itoa strmapi memset memchr memcpy \
		bzero memmove calloc putchar_fd putstr_fd \
		putendl_fd putnbr_fd striteri \
		lstnew lstadd_front lstsize \
		lstlast lstadd_back lstdelone \
		lstclear lstiter lstmap get_next_line tmp
SRC = $(addprefix $(SRC_DIR)/ft_, $(addsuffix .c, $(SRC_FILES)))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -MMD -MP -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)