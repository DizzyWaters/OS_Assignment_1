# === Compiler and Flags ===
CC := gcc
CFLAGS := -Wall -Wextra -std=c11
SOURCE_DIR := source
BUILD_DIR := build

# === Targets ===
DEBUG_DIR := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release
TARGET := OS_TASK_1_App

# === Sources and Objects ===
SRC := $(wildcard $(SOURCE_DIR)/*.c)
OBJ_DEBUG := $(patsubst $(SOURCE_DIR)/%.c, $(DEBUG_DIR)/%.o, $(SRC))
OBJ_RELEASE := $(patsubst $(SOURCE_DIR)/%.c, $(RELEASE_DIR)/%.o, $(SRC))

# === Default target ===
all: release

# === Debug build ===
debug: CFLAGS += -g -O0
debug: $(DEBUG_DIR)/$(TARGET)

# === Release build ===
release: CFLAGS += -O2
release: $(RELEASE_DIR)/$(TARGET)

# === Linking ===
$(DEBUG_DIR)/$(TARGET): $(OBJ_DEBUG)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "✅ Built DEBUG executable: $@"

$(RELEASE_DIR)/$(TARGET): $(OBJ_RELEASE)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) $^ -o $@
	@echo "🚀 Built RELEASE executable: $@"

# === Compilation Rules ===
$(DEBUG_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# === Cleanup ===
clean:
	rm -rf $(BUILD_DIR)
	@echo "🧹 Cleaned build directories."

.PHONY: all debug release clean
