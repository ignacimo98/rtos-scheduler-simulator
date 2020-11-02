#include "scheduler.h"

alien* schedule_alien(alien aliens[], int alien_amount, algorithm algorithm) {
  alien* to_schedule = &(aliens[0]);
  int i = 0;
  for (; i < alien_amount; ++i) {
    if (aliens[i].remaining_energy > 0) {
      to_schedule = &(aliens[i]);
      break;
    }
  }

  // TODO: Calendarizar la mica
  if (algorithm == RMS) {
    for (; i < alien_amount; i++) {
      if (aliens[i].period < to_schedule->period && aliens[i].remaining_energy > 0){
        to_schedule = &(aliens[i]);
      }
    }
  } else {

  }
  return to_schedule;
}
