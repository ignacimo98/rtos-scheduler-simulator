#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "alien.h"

typedef enum algorithm { RMS, EDF } algorithm;
int deadline_check(alien aliens[], int alien_amount, int time);
alien* schedule_alien(alien aliens[], int alien_amount, int *alien_number, algorithm algorithm);

#endif //SCHEDULER_H_