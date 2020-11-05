#ifndef ALIEN_H_
#define ALIEN_H_
#include <stdlib.h>
#include "directions.h"

typedef enum status { NOT_INITIALIZED, RUNNING, TERMINATED} status;

typedef struct alien
{
  int x, y;
  float r, g, b;
  int period, creation_time, energy, remaining_energy, next_deadline;
  status status;

} alien;

void initialize_aliens(alien aliens[], int max_alien_amount);
void initialize_alien(alien* alien, int period, int creation_time, int energy, status status, char *maze, int maze_height, int maze_width);
void move_alien(alien* alien, directions available_directions, int width, int height);
void alienate_maze(alien aliens[], int alien_amount, char* maze, int maze_width);
void dealienate_maze(alien aliens[], int alien_amount, char* maze, int maze_width);

#endif //ALIEN_H_
