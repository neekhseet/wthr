CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g -Iincludes

LDFLAGS = -lcurl

TARGET = wthr
SRC_DIR  := sources
OBJ_DIR  := obj

SRCS     := $(wildcard $(SRC_DIR)/*.c)

OBJS     := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

PREFIX = /usr/local/bin

install: $(TARGET)
	@echo "Подготовка директории и установка утилиты в $(PREFIX)..."
	sudo mkdir -p $(PREFIX)
	sudo cp $(TARGET) $(PREFIX)/

uninstall:
	@echo "Удаление утилиты из $(PREFIX)..."
	sudo rm -f $(PREFIX)/$(TARGET)



clean:
	rm -rf $(TARGET) $(OBJ_DIR)

.PHONY: all clean install uninstall

