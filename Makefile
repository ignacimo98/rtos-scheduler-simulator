FLAGS=-Wall -g
CC=gcc
all:
	$(CC) ${FLAGS} src/allegro_maze.c -o bin/maze -lallegro -lallegro_primitives -lallegro_main -lallegro_font -lallegro_ttf
clean:
	rm -f bin/maze
