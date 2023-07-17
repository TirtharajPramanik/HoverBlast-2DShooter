.PHONY := run build clean
ARGS := $(shell pkg-config --libs --cflags raylib)
FILE := main

run: build
	./${FILE}

build: ${FILE}.c
	eval cc ${FILE}.c $(ARGS) -o ${FILE}

clean:
	rm ${FILE}