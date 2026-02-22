# Makefile for LSL2 project

# Compiler and flags
CC := gcc
CFLAGS := -Wall -Wextra -O2 -I./src/core

# Directories
SRC_DIR := src
CORE_DIR := $(SRC_DIR)/core
BUILD_DIR := build

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(CORE_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Discover directories where objects will live (used for mkdir)
OBJ_DIRS := $(sort $(dir $(OBJS)))

# Target executable
TARGET := lsl2

.PHONY: all clean directories

all: directories $(TARGET)

# Link the program
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each object
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(CORE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory (and subdirs) exist
directories:
	@mkdir -p $(OBJ_DIRS)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
