CC = gcc
CFLAGS = -Wall
DEFINE_OPTIONS = -DVOS_DEBUG
INC_HEADER = -I../../competition/vos_cstl
LIBS = -lm

target := $(patsubst %.c, %, $(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) $(DEFINE_OPTIONS) $(INC_HEADER) $< -o $@ $(LIBS)

all: $(target)

clean:
	rm $(target)
