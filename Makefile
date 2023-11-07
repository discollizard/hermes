CFLAGS = -g3 -o hermes.out
FILES = main.c webfunctions.c debug.c data_structures.c 

all: final

final:
	gcc $(FILES) $(CFLAGS)