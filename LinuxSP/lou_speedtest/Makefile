CC = gcc
INC = -I./inc ./main.h
SRC = ./src/*.c
FLAG = -lm -lpthread -lssl -lcrypto
BIN = ./bin/speedtest
DB_GDB = ./bin/speedtest-gdbdebug

all: main

main: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -o $(BIN) $(FLAG)

debug_memory: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -std=c11 -lm -o debug
	valgrind --track-origins=yes --leak-check=full ./debug
	rm -rf debug

debug_gdb: main.c $(SRC)
	$(CC) $(INC) main.c $(SRC) -o $(DB_GDB) -g $(FLAG)
	gdb $(DB_GDB)
	rm -rf $(DB_GDB)

run:
	$(BIN)

clean:
	rm -rf $(BIN)