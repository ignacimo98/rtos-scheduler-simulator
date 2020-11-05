#ifndef MAZE_H_
#define MAZE_H_

#include "maze_platform.h"
#include "directions.h"
#include "alien.h"

#include <stdlib.h>
#include <time.h>

#define internal static
#define local_persist static
#define global_variable static

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height);

directions get_available_directions(char* maze, int width, int height, int x,
                                    int y, alien aliens[], int alien_amount);


#endif
