CC=gcc
CFLAGS=-c -std=c89 -Wall -Werror -pedantic


table_editor: main.o functions.o
	$(CC) main.o functions.o -o table_editor


main: main.c header.h
	$(CC) $(CFLAGS) main.c -lm


table: table.c header.h
	$(CC) $(CFLAGS) table.c


clean:
	rm -rf *.o
