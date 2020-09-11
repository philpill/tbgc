CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc

all: build run

run:
	./bin/main

build:
	${CC} $(CFLAGS) src/*.c -g -o ./bin/main

install:
	mkdir log bin; apt-get install libsdl2-dev

clean:
	rm ./*gch ./*swp ./*swo ./bin/* ./log/*