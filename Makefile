CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc

all: build run

run:
	./bin/main

build:
	${CC} $(CFLAGS) src/main.c -IC:\dev\SDL2-2.0.12\i686-w64-mingw32\include\SDL2 -LC:\dev\SDL2-2.0.12\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 -o ./bin/main

install:
	mkdir log bin; apt-get install libsdl2-dev

clean:
	rm ./*gch ./*swp ./*swo ./bin/* ./log/*