CFLAGS = -Wall -Wextra -Werror
CC = gcc
target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $< -o $@

all: $(target)

clean:
	rm $(target)
