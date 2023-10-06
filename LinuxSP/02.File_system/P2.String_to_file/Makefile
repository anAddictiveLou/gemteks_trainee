CC = gcc

all: main.c
	$(CC) main.c -o main

run: all
	./main

debug_memory: main.c 
	$(CC) main.c -std=c11 -lm -o debug
	valgrind --track-origins=yes --leak-check=full ./debug
	rm -rf debug

debug_gdb: main.c 
	$(CC) main.c -o gdb_debug -g
	gdb ./gdb_debug
	rm -rf gdb_debug

clean:
	rm -rf main