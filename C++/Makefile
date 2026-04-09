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
CC = c++
CFLAGS = -Wall -Wextra -Werror
NAME = rush02
HEADER = rush02.hpp

# Directories
SRC_DIR = src/
OBJ_DIR = obj/

# Files
SRC_FILES = rush02.cpp utils.cpp
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))

### RULES ###

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)


$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(HEADER) | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)... $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(CYAN)-> $(NAME) compiled.$(DEF_COLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C ../libft
	@echo "$(BLUE)-> $(NAME) object files cleaned.$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C ../libft
	@echo "$(RED)-> $(NAME) removed.$(DEF_COLOR)"

re: fclean all
	@echo "$(CYAN)-> Cleaned and rebuilt $(NAME) from scratch.$(DEF_COLOR)"

.PHONY: all clean fclean re