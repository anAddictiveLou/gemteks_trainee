CC = gcc
INC = -I./inc ./main.h
SRC = ./src/*.c
FLAG = -lm -lpthread 
BIN = ./bin/speedtest

all: main

main: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -o $(BIN) $(FLAG)

debug_memory: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -std=c11 -lm -o debug
	valgrind --track-origins=yes --leak-check=full ./debug
	rm -rf debug

debug_gdb: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -o gdb_debug -g
	gdb ./gdb_debug
	rm -rf gdb_debug

run:
	$(BIN)

clean:
	rm -rf $(BIN)