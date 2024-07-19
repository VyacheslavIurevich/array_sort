TARGET = array_sortSRC_DIR = src
OBJ_DIR = obj
CFLAGS = -Wall -Wextra -pedantic -Werror -O2
CC = gcc
SRC_FILES_C = $(shell find $(SRC_DIR) -name '*.c')
SRC_FILES_S = $(shell find $(SRC_DIR) -name '*.s')
OBJ_FILES_C = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES_C))
OBJ_FILES_S = $(patsubst $(SRC_DIR)/%.s, $(OBJ_DIR)/%.o, $(SRC_FILES_S))
OBJ_FILES = $(OBJ_FILES_C) $(OBJ_FILES_S)
$(TARGET): $(OBJ_FILES)
 $(CC) $(CFLAGS) -o $@ $^
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
 @mkdir -p $(dir $@)
 $(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s | $(OBJ_DIR)
 @mkdir -p $(dir $@)
 $(CC) $(CFLAGS) -c -o $@ $<
$(OBJ_DIR):
 mkdir -p $(OBJ_DIR)
clean:
 rm -rf $(OBJ_DIR) $(TARGET)
format:
 find . -regex '.*\.\(c\|h\|cpp\|hpp\)' -exec clang-format -style=file -i {} \;
.PHONY: clean format
