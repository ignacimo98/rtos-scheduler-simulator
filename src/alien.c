#include "alien.h"

#include <stdio.h>

void initialize_aliens(alien aliens[], int max_alien_amount) {
  for (int i = 0; i < max_alien_amount; ++i) {
    printf("%d\n", i);
    initialize_alien(&(aliens[i]), 0, 0, 0, NOT_INITIALIZED);
  }
}

void initialize_alien(alien* alien, int period, int creation_time, int energy,
                      status status) {
  alien->x = 1;
  alien->y = 0;
  alien->period = period;
  alien->creation_time = creation_time;
  alien->next_deadline = period + creation_time;
  alien->energy = energy;
  alien->remaining_energy = energy;
  alien->r = (float)rand() / (float)RAND_MAX;
  alien->g = (float)rand() / (float)RAND_MAX;
  alien->b = (float)rand() / (float)RAND_MAX;
  alien->status = status;
}

void move_alien(alien* alien, directions available_directions) {
  while (1) {
    int dir = rand() % 4;  // 0 up, 1 down, 2 left, 3 right
    if (dir == 0 && available_directions.up) {
      alien->y--;
      break;
    } else if (dir == 1 && available_directions.down) {
      alien->y++;
      break;
    } else if (dir == 2 && available_directions.left) {
      alien->x--;
      break;
    } else if (dir == 3 && available_directions.right) {
      alien->x++;
      break;
    }
  }
}