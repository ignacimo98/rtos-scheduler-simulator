#ifndef MAZE_H
#define MAZE_H

#include "maze_platform.h"

#include <stdlib.h>
#include <time.h>

#define internal static
#define local_persist static
#define global_variable static

typedef struct directions
{
  char up, down, left, right;
} directions;

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height);

directions get_available_directions(char* maze, int width, int height, int x,
                                    int y);

#endif
