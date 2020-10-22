#include "alien.h"

void initialize_alien(alien* alien, int period, int creation_time, int energy){
  alien->x = 1;
  alien->y = 0;
  alien->period = period;
  alien->creation_time = creation_time;
  alien->energy = energy;
  alien->remaining_energy = energy;
  alien->r = (float)rand()/(float)RAND_MAX;
  alien->g = (float)rand()/(float)RAND_MAX;
  alien->b = (float)rand()/(float)RAND_MAX;
}