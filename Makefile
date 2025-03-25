# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Define the source files
SRC = main.c helper.c

# Define the object files (one for each source file)
OBJ = main.o helper.o

# Define the executable name
EXEC = my_shell

# Libraries to link
LIBS = -lreadline -lncurses

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ) $(LIBS)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean
