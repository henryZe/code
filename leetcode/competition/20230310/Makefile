CC = gcc
CFLAGS = -Wall -Wextra
DEFINE_OPTIONS = -DVOS_DEBUG
INC_HEADER = -I../vos_cstl
LIBS = -L../securec -lsecurec

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(DEFINE_OPTIONS) $(INC_HEADER) $< -o $@ $(LIBS)

all: $(target)

clean:
	rm $(target)
