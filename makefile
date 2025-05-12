# Makefile para el laboratorio 2 de Electronica IV

CC := gcc

SRC_DIR := src
INC_DIR := inc
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
DOC_DIR := $(BUILD_DIR)/doc

CFLAGS := -Wall -Wextra -Werror -std=c99 -I$(INC_DIR)
LDFLAGS := 
DEPFLAGS := -MMD -MP

NAME := lab2
TARGET := $(BIN_DIR)/$(NAME)

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.d,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR) $(DOC_DIR): | $(BUILD_DIR)
	@mkdir -p $@

$(BUILD_DIR):
	@mkdir -p $@

doc: | $(DOC_DIR)
	doxygen Doxyfile

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

distclean: clean
	@rm -rf $(DOC_DIR)

-include $(DEPS)
