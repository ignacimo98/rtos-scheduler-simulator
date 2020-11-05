#include "scheduler.h"
#include <stdio.h>

int deadline_check(alien aliens[], int alien_amount, int time){
  int overflow = 0;
  //printf("In deadline check time is: %d\n",time);
  for(int i = 0; i < alien_amount; i++){
    //printf("Time is: %d next deadline in :%d remain energy:%d\n",time,aliens[i].next_deadline, aliens[i].remaining_energy);
    if (time == aliens[i].next_deadline){
      if (aliens[i].remaining_energy != 0){
        // Scheduler_Overflow!!!
        printf("OVERFLOW!!!\n");
        overflow = 1;
      } else {
        aliens[i].next_deadline += aliens[i].period;
        aliens[i].remaining_energy = aliens[i].energy;
        //printf("Energy restored! \n");
      }
    }
  }
  return overflow;
}

alien* schedule_alien(alien aliens[], int alien_amount, int *alien_number, algorithm algorithm) {
  alien* to_schedule = NULL;
  
  //Check for deadlines
  
  int i = 0;
  for (; i < alien_amount; ++i) {
    if (aliens[i].remaining_energy > 0 && aliens[i].status == RUNNING) {
      to_schedule = &(aliens[i]);
      *alien_number = i+1;
      break;
    }
  }

  if (algorithm == RMS) {
    // ___________ RMS Scheduler __________
    for (; i < alien_amount; i++) {
      if (aliens[i].period < to_schedule->period && aliens[i].remaining_energy > 0 && aliens[i].status == RUNNING){
        to_schedule = &(aliens[i]);
        *alien_number = i+1;
      }
    }
  } else {
    // ___________ EDF Scheduler __________
    for (; i < alien_amount; i++) {
      if (aliens[i].next_deadline < to_schedule->next_deadline && aliens[i].remaining_energy > 0 && aliens[i].status == RUNNING){
        to_schedule = &(aliens[i]);
        *alien_number = i+1;
      }
    }
  }
  return to_schedule;
}
