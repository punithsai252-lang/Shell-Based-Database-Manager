CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer

SRC = src/main.c src/database.c src/input.c src/parser.c src/process.c src/builtin.c src/signals.c src/pipes.c src/redirect.c
TARGET = bin/shellforge

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf bin/*

asan: $(SRC)
	mkdir -p bin
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $(SRC) -o bin/shellforge-asan
