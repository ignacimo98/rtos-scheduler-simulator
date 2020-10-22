#ifndef MAZE_H
#define MAZE_H

#include "maze_platform.h"

#include <stdlib.h>
#include <time.h>

#define internal static
#define local_persist static
#define global_variable static

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height);

#endif
