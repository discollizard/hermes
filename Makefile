CFLAGS = -g3 -g -o
FILES = main.c webfunctions.c debug.c

all: final

final:
	gcc $(FILES) $(CFLAGS) hermes.out
