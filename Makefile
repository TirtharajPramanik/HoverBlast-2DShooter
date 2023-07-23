.PHONY := run build_ clean
ARGS := $(shell pkg-config --libs --cflags raylib)
FILE := main

run: build_
	./${FILE}

build_: ${FILE}.c
	eval cc ${FILE}.c $(ARGS) -o ${FILE}

clean:
	rm -r ${FILE} ${FILE}.dSYM