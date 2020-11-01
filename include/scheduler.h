#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "alien.h"

typedef enum algorithm { RMS, EDF } algorithm;

alien schedule_alien(alien aliens[], int alien_amount, algorithm algorithm);

#endif //SCHEDULER_H_