CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic -O2

OBJS := $(patsubst %.c,%.o,$(wildcard src/*.c))
TARGET := main

.PHONY: all clean

all: $(TARGET)

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -Iinclude/ $(addprefix -I,$(LIB_DIRS)) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o build/$@

clean:
	rm -f $(filter-out %.c, $(wildcard src/*))
	rm -f $(wildcard build/*)
