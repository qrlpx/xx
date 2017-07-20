CC = gcc
CFLAGS = -ansi -pedantic -g -Wall -Wextra
OBJS = build/mpc.o build/xx_ast.o build/xx_main.o

all: build $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o build/test

build:
	mkdir build

build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.c: %.h

.PHONY: clean
clean:
	rm build/*
