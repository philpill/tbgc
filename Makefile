CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc
DEPS = src/stb_image.h

OBJS = src/main.c src/render.c src/event.c src/player.c src/utils.c src/level.c src/asset.c
OBJS_TEST = src/render.c src/event.c src/player.c src/utils.c src/level.c  src/asset.c src/test/test.c src/test/render.c

INCLUDE_PATHS = -IC:/dev/SDL2-2.0.12/i686-w64-mingw32/include/SDL2
INCLUDE_PATHS_TEST = ${INCLUDE_PATHS} -I"C:/Program Files (x86)/cmocka/include"

LIBRARY_PATHS = -LC:/dev/SDL2-2.0.12/i686-w64-mingw32/lib
LIBRARY_PATHS_TEST = ${LIBRARY_PATHS} -L"C:\Program Files (x86)\cmocka\bin"

# https://stackoverflow.com/a/34540492
# COMPILER_FLAGS = -w -Wl,-subsystem,windows
COMPILER_FLAGS = -w

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
LINKER_FLAGS_TEST = ${LINKER_FLAGS} -lcmocka

OBJ_NAME = bin\tbgc
OBJ_NAME_TEST = bin\tbgc_test

.PHONY: all clean

all: build run

run:
	$(OBJ_NAME)

build:$(OBJS) $(DEPS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	del *swp *swo *exe bin\*.* /q

test:$(OBJS_TEST) $(DEPS) 
	COPY "lib\cmocka.dll" "bin\cmocka.dll"
	$(CC) $(OBJS_TEST) $(INCLUDE_PATHS_TEST) $(LIBRARY_PATHS_TEST) $(COMPILER_FLAGS) $(LINKER_FLAGS_TEST) -o $(OBJ_NAME_TEST) && $(OBJ_NAME_TEST)