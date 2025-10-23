CC := gcc
CFLAGS := -Wall -Wextra -std=c11
SOURCE_DIR := source
BUILD_DIR := build

#targets
DEBUG_DIR := $(BUILD_DIR)/debug
RELEASE_DIR := $(BUILD_DIR)/release
TARGET := OS_TASK_1_App

# .o and sources

SRC := $(wildcard $(SOURCE_DIR)/*.c)
OBJ_DEBUG := $(patsubst $(SOURCE_DIR)/%.c, $(DEBUG_DIR)/%.o, $(SRC))
OBJ_RELEASE := $(patsubst $(SOURCE_DIR)/%.c, $(RELEASE_DIR)/%.o, $(SRC))

all: release

# debug rules
debug: CFLAGS += -g -O0
debug: $(DEBUG_DIR)/$(TARGET)
# delease rules
release: CFLAGS += -O2
release: $(RELEASE_DIR)/$(TARGET)

$(DEBUG_DIR)/$(TARGET): $(OBJ_DEBUG)
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(RELEASE_DIR)/$(TARGET): $(OBJ_RELEASE)
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(DEBUG_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all debug release clean