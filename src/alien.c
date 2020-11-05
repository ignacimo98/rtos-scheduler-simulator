#include "alien.h"

void initialize_aliens(alien aliens[], int max_alien_amount) {
  char maze = 0;
  for (int i = 0; i < max_alien_amount; ++i) {
    initialize_alien(&(aliens[i]), 0, 0, 0, NOT_INITIALIZED, &maze, 0, 0);
  }
}

void initialize_alien(alien* alien, int period, int creation_time, int energy,
                      status status, char* maze, int maze_height,
                      int maze_width) {
  int x = 0, y = 0;

  while (*maze) {
    x = (rand() % (maze_width - 1));
    y = (rand() % (maze_height - 1));
    if (!maze[y * maze_width + x]) {
      break;
    }
  }

  alien->x = x;
  alien->y = y;
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

void move_alien(alien* alien, directions available_directions, int width, int height) {
  // TODO: que salgan los aliens del laberinto
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
  if (alien->x == width-2 && alien->y == height-1)
    alien->status = TERMINATED;
}

void alienate_maze(alien aliens[], int alien_amount, char* maze, int maze_width){
  for (int i = 0; i < alien_amount; ++i){
    maze[aliens[i].y * maze_width + aliens[i].x] = 1;
  }
}

void dealienate_maze(alien aliens[], int alien_amount, char* maze, int maze_width){
  for (int i = 0; i < alien_amount; ++i){
    maze[aliens[i].y * maze_width + aliens[i].x] = 0;
  }
}