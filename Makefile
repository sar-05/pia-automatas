CFLAGS  := -Wall -Wextra -std=c99 -pedantic -Iinclude/ -Ilibs/isocline/include/ -Ilibs/optparse -MMD -MP
LDFLAGS :=
SRCS    := $(wildcard src/*.c)
LIB_SRCS := libs/isocline/src/isocline.c
NAME    := TA_033_PIA_E3
DEBUG_OBJS   := $(patsubst src/%.c, build/debug/%.o,   $(SRCS)) \
                $(patsubst libs/%.c, build/debug/libs/%.o,   $(LIB_SRCS))
RELEASE_OBJS := $(patsubst src/%.c, build/release/%.o, $(SRCS)) \
                $(patsubst libs/%.c, build/release/libs/%.o, $(LIB_SRCS))

.PHONY: all debug release clean help

all: debug

debug:   build/$(NAME)_debug
release: build/$(NAME)

build/debug/%.o: src/%.c | build/debug
	$(CC) $(CFLAGS) -g -O0 -c $< -o $@

build/release/%.o: src/%.c | build/release
	$(CC) $(CFLAGS) -O2 -DNDEBUG -c $< -o $@

build/debug/libs/%.o:   libs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -O0 -c $< -o $@

build/release/libs/%.o: libs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O2 -DNDEBUG -c $< -o $@

build/$(NAME)_debug: $(DEBUG_OBJS) | build
	$(CC) $(LDFLAGS) $^ -o $@

build/$(NAME): $(RELEASE_OBJS) | build
	$(CC) $(LDFLAGS) $^ -o $@

build build/debug build/release build/debug/libs build/release/libs:
	mkdir -p $@

help:
	@echo "Targets: all, debug, release, clean"

clean:
	rm -rf build/debug build/release

-include $(wildcard build/debug/*.d build/release/*.d)
