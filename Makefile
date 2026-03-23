### COLORS ###
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

### VARIABLES ###
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = rush02
HEADER = include/rush.h

# Directories
SRC_DIR = src/

# Files
SRC_FILES = rush02.c utils.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

### RULES ###

all: $(NAME)

# Creating the archive
$(NAME):
	@echo "$(YELLOW)Compiling $(NAME)... $(DEF_COLOR)"
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(SRC) ./libft/libft.a -o $(NAME) 
	@echo "$(CYAN)-> $(NAME) compiled.$(DEF_COLOR)"

clean:
	@rm -f $(NAME)
	@echo "$(BLUE)-> $(NAME) executable cleaned!$(DEF_COLOR)"

fclean: clean
	@$(MAKE) fclean -C ./libft
	@echo "$(RED)-> $(NAME) removed.$(DEF_COLOR)"

re: fclean all
	@echo "$(CYAN)-> Cleaned and rebuilt $(NAME) from scratch.$(DEF_COLOR)"

.PHONY: all clean fclean re