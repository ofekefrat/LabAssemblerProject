CC = gcc
CFLAGS = -ansi -Wall -pedantic
DEPS = preassemble.h libraries.h
OBJ = main.o preassemble.o mcr.o

%.o:  %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
