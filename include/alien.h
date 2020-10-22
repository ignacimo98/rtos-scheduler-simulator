#include <stdlib.h>

typedef struct alien
{
  int x, y;
  float r, g, b;
  int period, creation_time, energy, remaining_energy;

} alien;

void initialize_alien(alien* alien, int period, int creation_time, int energy);


