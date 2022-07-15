CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -Werror
INC_HEADER = -I../vos_cstl

LIB_OBJFILES := $(patsubst %.c, %.o, $(wildcard *.c))
TARFET_OBJ = libsecurec.a

%.o: %.c
	$(CC) $(CFLAGS) $(INC_HEADER) -c -o $@ $<

$(TARFET_OBJ): $(LIB_OBJFILES)
	$(AR) r $@ $(LIB_OBJFILES)

all: $(TARFET_OBJ)

clean:
	rm $(LIB_OBJFILES) $(TARFET_OBJ)
