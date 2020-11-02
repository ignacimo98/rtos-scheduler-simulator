#include "scheduler.h"

int deadline_check(alien aliens[], int alien_amount, int time){
  for(int i = 0; i < alien_amount; i++){
    if (time == aliens[i].next_deadline){
      if (aliens[i].energy != 0){
        // Scheduler_Overflow!!!
        //end exec
      } else {
        aliens[i].next_deadline += aliens[i].period;
        aliens[i].remaining_energy = aliens[i].energy;
      }
    }
  }
}

alien* schedule_alien(alien aliens[], int alien_amount,int time, algorithm algorithm) {
  alien* to_schedule = NULL;
  
  //Check for deadlines

  
  int i = 0;
  for (; i < alien_amount; ++i) {
    if (aliens[i].remaining_energy > 0) {
      to_schedule = &(aliens[i]);
      break;
    }
  }

  // TODO: Calendarizar la mica
  if (algorithm == RMS) {
    // ___________ RMS Scheduler __________
    for (; i < alien_amount; i++) {
      if (aliens[i].period < to_schedule->period && aliens[i].remaining_energy > 0){
        to_schedule = &(aliens[i]);
      }
    }
  } else {
    // ___________ EDF Scheduler __________


  }
  return to_schedule;
}
