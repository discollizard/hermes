CFLAGS = -o
FILES = main.c webfunctions.c debug.c

all: final

final:
	mkdir -p /var/hermes/html && clang $(FILES) $(CFLAGS) hermes.out
