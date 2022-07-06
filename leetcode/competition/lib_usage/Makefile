CC = gcc
CFLAGS = -Wall -Werror
INC_HEADER = -I../vos_cstl_header

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(INC_HEADER) $< -o $@

all: $(target)

clean:
	rm $(target)
