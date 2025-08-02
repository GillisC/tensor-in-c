CC = gcc
CFLAGS = -Wall -g -Wextra -Iinclude -DTESTA_USE_COLOR

SRC_DIR = src
BUILD_DIR = build
BIN = $(BUILD_DIR)/main

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))
OBJ_FILES_NO_MAIN = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES_NO_MAIN))

TEST_DIR = tests
TEST_BIN = $(BUILD_DIR)/test_runner

TEST_SRC_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/tests/%.o, $(TEST_SRC_FILES))
TEST_FRAMEWORK_OBJ = $(BUILD_DIR)/testa.o

# MAIN EXECUTABLE TARGETS

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


# TESTING TARGETS

# force it to rebuild entire project each time
test: $(TEST_BIN) | $(BUILD_DIR)/tests
	@$(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ_FILES) $(TEST_FRAMEWORK_OBJ) $(OBJ_FILES_NO_MAIN) | $(BUILD_DIR)
	@$(CC) $^ -o $@

$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.c | $(BUILD_DIR)/tests 
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_FRAMEWORK_OBJ): $(SRC_DIR)/testa.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/tests:
	@mkdir -p $(BUILD_DIR)/tests


clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all test clean force


