FLAGS=-Wall -g
CC=gcc
all:
	$(CC) ${FLAGS} src/allegro_maze.c -o bin/maze -lallegro -lallegro_primitives -lallegro_main
clean:
	rm -f bin/maze
