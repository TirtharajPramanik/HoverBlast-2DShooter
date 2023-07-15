.PHONY := run build clean
ARGS := $(shell pkg-config --libs --cflags raylib)

run: build
	./player

build: player.c
	eval cc player.c $(ARGS) -o player

clean:
	rm player