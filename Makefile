CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc

OBJS = src/main.c

INCLUDE_PATHS = -IC:\dev\SDL2-2.0.12\i686-w64-mingw32\include\SDL2

LIBRARY_PATHS = -LC:\dev\SDL2-2.0.12\i686-w64-mingw32\lib

COMPILER_FLAGS = -w -Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OBJ_NAME = tbgc

all: build run

run:
	./bin/main

build:$(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

install:
	mkdir log bin; apt-get install libsdl2-dev

clean:
	rm ./*gch ./*swp ./*swo ./bin/* ./log/*