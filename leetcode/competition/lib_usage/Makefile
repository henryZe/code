CC = gcc
CFLAGS = -Wall -Werror -static
INC_HEADER = -I../vos_cstl
LIBS = -L../securec -lsecurec

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(INC_HEADER) $< -o $@ $(LIBS)

all: $(target)

clean:
	rm $(target)
