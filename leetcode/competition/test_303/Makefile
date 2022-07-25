CC = gcc
CFLAGS = -Wall
DEFINE_OPTIONS = -DVOS_DEBUG
INC_HEADER = -I../vos_cstl

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(DEFINE_OPTIONS) $(INC_HEADER) $< -o $@

all: $(target)

clean:
	rm $(target)
