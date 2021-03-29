all:
	gcc -Ilist/ server.c list/list.c -o server -lpthread
	gcc client.c -o client

clean:
	rm -rf *.o server client

.PHONY:clean
