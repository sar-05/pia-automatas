CC     := gcc
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic -Iinclude/
SRCS   := $(wildcard src/*.c)
NAME   := main

.PHONY: all debug release clean

all: debug

debug:   build/$(NAME)_debug
release: build/$(NAME)

build/debug/%.o: src/%.c | build/debug
	$(CC) $(CFLAGS) -g -O0 -c $< -o $@

build/release/%.o: src/%.c | build/release
	$(CC) $(CFLAGS) -O2 -DNDEBUG -c $< -o $@

build/$(NAME)_debug:   $(patsubst src/%.c, build/debug/%.o,   $(SRCS)) | build
	$(CC) $(CFLAGS) $^ -o $@

build/$(NAME): $(patsubst src/%.c, build/release/%.o, $(SRCS)) | build
	$(CC) $(CFLAGS) $^ -o $@

build build/debug build/release:
	mkdir -p $@

clean:
	rm -rf build/
