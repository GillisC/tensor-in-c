CC = gcc
CFLAGS = -Wall -g -Wextra -Iinclude

SRC_DIR = src
BUILD_DIR = build
BIN = $(BUILD_DIR)/main

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

# default
all: $(BIN)
	@$(BIN)

# linking rule (the binary requires that the object files are linked together)
$(BIN): $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) -o $@

# compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# create the build directory is not created already
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all clean


