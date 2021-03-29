SRC = $(wildcard *.c)
BIN :=$(patsubst %.c,%,$(SRC))

#all是终极目标,在这里也是伪目标,隐式规则
all:$(BIN)

#?=变量是否已经被定义
FLAGS ?= -Wall -O0
FLAGS += -g

CROSS_COMPILE = arm-linux-
ifdef CROSS_COMPILE
	CC = $(CROSS_COMPILE)gcc
else
	CC = gcc
endif

#模式规则部分
$(BIN):%:%.c
	$(CC) $^ -o $@ $(FLAGS)

clean:
	rm $(BIN)

#all和clean都是伪目标,为了防止应用隐式规则,用.PHONY标明
.PHONY:all clean


