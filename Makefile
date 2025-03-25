# Compiler
CC = cc

# Flags
CFLAGS = #-Wall -Werror -Wextra
LDFLAGS = -lreadline

# Directories
HEADER_DIR = includes
SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = bonus
BONUS_OBJ_DIR = bonus_obj
LIBFT_DIR = libft

# Libraries
LIBS = -L$(LIBFT_DIR) -lft

# Source files
SRC = minishell.c

# Bonus source files
BONUS_SRC = 

# Object files
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Bonus object files
BONUS_OBJ = $(BONUS_SRC:%.c=$(BONUS_OBJ_DIR)/%.o)

# Executable names
NAME = mini
BONUS_NAME = mini_bonus

# Include directories
INCLUDES = -I$(HEADER_DIR)

# Rules
all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(LDFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBS) $(LDFLAGS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
