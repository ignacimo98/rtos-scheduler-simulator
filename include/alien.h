#ifndef ALIEN_H_
#define ALIEN_H_

#include <stdlib.h>

#include "maze.h"

typedef enum status { NOT_INITIALIZED, RUNNING, TERMINATED} status;

typedef struct alien
{
  int x, y;
  float r, g, b;
  int period, creation_time, energy, remaining_energy, next_deadline;
  status status;

} alien;

void initialize_aliens(alien aliens[], int max_alien_amount);
void initialize_alien(alien* alien, int period, int creation_time, int energy, status status);
void move_alien(alien* alien, directions available_directions);

#endif //ALIEN_H_
