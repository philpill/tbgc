CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc
DEPS = src/stb_image.h
OBJS = src/main.c src/render.c src/event.c src/player.c src/utils.c

INCLUDE_PATHS = -IC:\dev\SDL2-2.0.12\i686-w64-mingw32\include\SDL2

LIBRARY_PATHS = -LC:\dev\SDL2-2.0.12\i686-w64-mingw32\lib

# https://stackoverflow.com/a/34540492
# COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -w

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

OBJ_NAME = tbgc

.PHONY: all clean

all: build run

run:
	$(OBJ_NAME)

build:$(OBJS) $(DEPS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	del *swp *swo *exe