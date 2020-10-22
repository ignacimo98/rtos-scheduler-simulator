#include "maze.h"

/*  Carve the maze starting at x, y. */
void CarveMaze(char *maze, int width, int height, int x, int y) {
  int x1, y1;
  int x2, y2;
  int dx, dy;
  int dir, count;

  dir = rand() % 4;
  count = 0;
  while (count < 4) {
    dx = 0;
    dy = 0;
    switch (dir) {
      case 0:
        dx = 1;
        break;
      case 1:
        dy = 1;
        break;
      case 2:
        dx = -1;
        break;
      default:
        dy = -1;
        break;
    }
    x1 = x + dx;
    y1 = y + dy;
    x2 = x1 + dx;
    y2 = y1 + dy;
    if (x2 > 0 && x2 < width && y2 > 0 && y2 < height &&
        maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
      maze[y1 * width + x1] = 0;
      maze[y2 * width + x2] = 0;
      x = x2;
      y = y2;
      dir = rand() % 4;
      count = 0;
    } else {
      dir = (dir + 1) % 4;
      count += 1;
    }
  }
}

/* Generate maze in matrix maze with size width, height. */
void GenerateMaze(char *maze, int width, int height) {
  int x, y;

  /* Initialize the maze. */
  for (x = 0; x < width * height; x++) {
    maze[x] = 1;
  }
  maze[1 * width + 1] = 0;

  /* Seed the random number generator. */
  srand(time(0));

  /* Carve the maze. */
  for (y = 1; y < height; y += 2) {
    for (x = 1; x < width; x += 2) {
      CarveMaze(maze, width, height, x, y);
    }
  }

  /* Set up the entry and exit. */
  maze[0 * width + 1] = 0;
  maze[(height - 1) * width + (width - 2)] = 0;
}
directions get_available_directions(char *maze, int width, int height, int x,
                                    int y) {
  directions result;
  if (y == 0 && x == 1) {
    result.up = 0;
    result.down = 1;
    result.left = 0;
    result.right = 0;

    return result;
  }
  result.up = !maze[(y - 1) * width + x];
  result.down = !maze[(y + 1) * width + x];
  result.left = !maze[y * width + x - 1];
  result.right = !maze[y * width + x + 1];

  return result;
}