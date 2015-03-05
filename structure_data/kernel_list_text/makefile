CC=gcc

SRC=$(wildcard  *.c */*.c)
OBJS=$(patsubst %c,%o,$(SRC))
#OBJS=main.o add.o sub.o mul.o dvd.o   可以将变量都看作字符串

FLAG=-L/usr/lib -lm -g

NAME=$(wildcard *.c)
TARGET=$(patsubst %.c,%_exe,$(NAME))


$(TARGET):$(OBJS)
#	$(CC) $(OBJS) -o $(TARGET)
	$(CC) $^      -o $@  $(FLAG)

%.o:%.c
	$(CC) -c $<   -o $@  -g


.PHONY:clean  echo

echo:
	echo $(SRC)

clean:
	-rm $(TARGET) $(OBJS)
