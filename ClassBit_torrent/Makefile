# Variables
CC = gcc
CFLAGS = -std=c17 -O2 -Wall -g
LIBS = -lssl -lcrypto -lcurl
OBJ_DIR = bin
SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: main

# Rule to create the object directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the final executable
main: $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

# Clean rule to remove generated files
clean:
	rm -rf $(OBJ_DIR) main

# Phony targets
.PHONY: all clean
