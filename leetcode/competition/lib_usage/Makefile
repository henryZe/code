CC = gcc
CFLAGS = -Wall -Werror
INC_HEADER = -I../vos_cstl
LIBS = -L../securec -lsecurec

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(INC_HEADER) $(LIBS) $< -o $@

all: $(target)

clean:
	rm $(target)
