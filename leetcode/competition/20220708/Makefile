CC = gcc
CFLAGS = -Wall -Wextra
INC_HEADER = -I../vos_cstl

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(INC_HEADER) $< -o $@

all: $(target)

clean:
	rm $(target)
