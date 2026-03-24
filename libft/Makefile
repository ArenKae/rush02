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
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
HEADER = include/libft.h

# Directories
SRC_DIR = src/
GNL_DIR = gnl/
PRINTF_DIR = printf/
OBJ_DIR = obj/

# Files
SRC_FILES = ft_isdigit.c ft_isprint.c ft_isspace.c ft_strlen.c ft_strncmp.c ft_split.c
GNL_FILES = get_next_line.c get_next_line_utils.c
PRINTF_FILES = ft_printf.c ft_printf_functions.c ft_printf_num.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
GNL_SRC = $(addprefix $(GNL_DIR), $(GNL_FILES))
PRINTF_SRC = $(addprefix $(PRINTF_DIR), $(PRINTF_FILES))

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o)) \
      $(addprefix $(OBJ_DIR), $(GNL_FILES:.c=.o)) \
      $(addprefix $(OBJ_DIR), $(PRINTF_FILES:.c=.o))

### RULES ###

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compiling source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	@echo "$(YELLOW)..Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compiling get_next_line files
$(OBJ_DIR)%.o: $(GNL_DIR)%.c $(GNL_DIR)get_next_line.h | $(OBJ_DIR)
	@echo "$(YELLOW)..Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compiling ft_printf files
$(OBJ_DIR)%.o: $(PRINTF_DIR)%.c $(PRINTF_DIR)ft_printf.h | $(OBJ_DIR)
	@echo "$(YELLOW)..Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Creating the archive
$(NAME): $(OBJ)
	@echo "$(YELLOW)..Compiling libft$(DEF_COLOR)"
	@$(AR) $(NAME) $(OBJ)
	@echo "$(CYAN)..libft compiled.$(DEF_COLOR)"

clean:
	@echo "$(YELLOW)..Cleaning libft$(DEF_COLOR)"
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)..libft object files cleaned.$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)..libft archive cleaned.$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re