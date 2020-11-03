#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "alien.h"
#include "maze.h"
#include "scheduler.h"
#include "ui_helper.h"

// TODO: x para terminar

const real32 FPS = 60.0f;
const int32 screen_width = 1200;
const int32 screen_height = 800;
const real32 move_speed = 2.0f;

const int max_alien_amount = 100;
int alien_amount = 0;
ALLEGRO_COLOR bg;

void button_action_switch(int *manual) { *manual = !*manual; }
void button_action_switch_algorithm(algorithm *current_algorithm) {
  if (*current_algorithm == RMS)
    *current_algorithm = EDF;
  else
    *current_algorithm = RMS;
}

void button_action_add(alien aliens[], int aliens_running, 
                        char period[], int time, char energy[], char* maze, 
                        int maze_height, int maze_width) {

  if (!aliens_running && !time) {
    initialize_alien(&aliens[alien_amount], atoi(period), time, atoi(energy), RUNNING, maze, maze_height, maze_width);
  } else {
    initialize_alien(&aliens[alien_amount], atoi(period), time+1, atoi(energy), RUNNING, maze, maze_height, maze_width);
  }
  alien_amount++;
}
void button_action_start(int *aliens_running) {
  if (*aliens_running == 1)
    *aliens_running = 0;
  else
    *aliens_running = 1;
}
void button_action_restart(alien aliens[], int *aliens_running, int *overflow, int *time) {
  for (int i = 0; i < alien_amount; i++){
    aliens[i].status = NOT_INITIALIZED;
  }
  alien_amount = 0;
  *aliens_running = 0;
  *overflow = 0;
  *time = 0;
}

void show_maze(const char *maze, int width, int height, int maze_start_x,
               int maze_start_y, int square_side) {
  int x, y;
  bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0);
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      switch (maze[y * width + x]) {
        case 1:
          al_draw_filled_rectangle(
              maze_start_x + x * square_side, maze_start_y + y * square_side,
              maze_start_x + x * square_side + square_side,
              maze_start_y + y * square_side + square_side, bg);
          break;
        default:
          break;
      }
    }
    // printf("\n");
  }
}

void show_toolbar(toolbar_info toolbar, ALLEGRO_FONT *font, int maze_width,
                  int square_side, bool32 manual, int aliens_running,
                  algorithm current_algorithm, input_box currently_selected,
                  char *energy_text, char *period_text) {
  //_____________DRAW VERTICAL LINE
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.toolbar_width, 15, toolbar.toolbar_width,
               maze_width * square_side + 15, bg, 2);

  //_____________DRAW MODE
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base,
               toolbar.y_base, ALLEGRO_ALIGN_LEFT, "Mode:");
  if (manual == 1) {
    al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base + 80,
                 toolbar.y_base, ALLEGRO_ALIGN_LEFT, "Manual");
  } else {
    al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base + 80,
                 toolbar.y_base, ALLEGRO_ALIGN_LEFT, "Auto");
  }
  //_____________DRAW SWITCH BUTTON
  draw_button(font, al_map_rgba(100, 100, 255, 255), "SWITCH", toolbar.x_base,
              toolbar.ycoord_switch, toolbar.button_width,
              toolbar.button_height);

  //_____________DRAW Algorithm
  if (current_algorithm == RMS) {
    al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base,
                 toolbar.y_base + 90, ALLEGRO_ALIGN_LEFT, "Algorithm: RMS");
  } else {
    al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base,
                 toolbar.y_base + 90, ALLEGRO_ALIGN_LEFT, "Algorithm: EDF");
  }
  //_____________DRAW SWITCH Algorithm BUTTON
  draw_button(font, al_map_rgba(100, 100, 255, 255), "SWITCH", toolbar.x_base,
              toolbar.ycoord_switch_algo, toolbar.button_width,
              toolbar.button_height);

  //_____________DRAW SEPARATION LINE 1
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.x_base, toolbar.y_base + 110 + 85,
               toolbar.toolbar_width - 20, toolbar.y_base + 110 + 85, bg, 2);

  //_____________NEW ALIEN INPUTS AND ADD BUTTON
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base + 5,
               toolbar.y_base + 130 + 90, ALLEGRO_ALIGN_LEFT, "- NEW ALIEN -");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base,
               toolbar.ycoord_input1 - 30, ALLEGRO_ALIGN_LEFT, "ENERGY:");
  draw_input_box(font, energy_text, toolbar.x_base, toolbar.ycoord_input1,
                 toolbar.button_width, toolbar.button_height, ENERGY,
                 currently_selected);

  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base,
               toolbar.ycoord_input2 - 30, ALLEGRO_ALIGN_LEFT, "PERIOD:");
  draw_input_box(font, period_text, toolbar.x_base, toolbar.ycoord_input2,
                 toolbar.button_width, toolbar.button_height, PERIOD,
                 currently_selected);

  draw_button(font, al_map_rgba(100, 100, 255, 255), "+", toolbar.x_base,
              toolbar.ycoord_add, toolbar.button_width, toolbar.button_height);

  //_____________DRAW SEPARATION LINE 2
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.x_base, toolbar.ycoord_add + 60,
               toolbar.toolbar_width - 20, toolbar.ycoord_add + 60, bg, 2);

  //_____________DRAW START/STOP BUTTON
  if (aliens_running) {
    draw_button(font, al_map_rgba(247, 7, 30, 255), "STOP", toolbar.x_base,
                toolbar.ycoord_start, toolbar.button_width,
                toolbar.button_height);
  } else {
    draw_button(font, al_map_rgba(72, 237, 11, 255), "START", toolbar.x_base,
                toolbar.ycoord_start, toolbar.button_width,
                toolbar.button_height);
  }

  //_____________DRAW SEPARATION LINE 3
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.x_base, toolbar.ycoord_start + 60,
               toolbar.toolbar_width - 20, toolbar.ycoord_start + 60, bg, 2);

  //_____________DRAW RESET BUTTON
  draw_button(font, al_map_rgba(247, 7, 30, 255), "RESET", toolbar.x_base,
              toolbar.ycoord_reset, toolbar.button_width,
              toolbar.button_height);
}

void show_alien_info(alien aliens[], int info_start_x, int info_start_y,
                     int maze_width, int square_side, int *info_space,
                     ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font) {
  // Separation Line
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(info_start_x, 15, info_start_x, maze_width * square_side + 15,
               bg, 2);
  al_draw_line(info_start_x + 280, 15, info_start_x + 280,
               maze_width * square_side + 15, bg, 2);

  // Column headers
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), info_start_x + 25, 10,
               ALLEGRO_ALIGN_LEFT, "Alien");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), info_start_x + 95, 10,
               ALLEGRO_ALIGN_LEFT, "Energy");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), info_start_x + 185, 10,
               ALLEGRO_ALIGN_LEFT, "Period");

  // Alien information deployment

  int ypos = 0;
  int xcol = 0;
  int column = 0;
  int max_rows = 19;
  for (int i = 0; i < alien_amount; ++i) {
    // Resize Window if needed
    if (i == *info_space) {
      al_resize_display(display, screen_width + 280 * (xcol), screen_height);
      *info_space += 20;
    }
    float r = aliens[i].r;
    float g = aliens[i].g;
    float b = aliens[i].b;
    bg = al_map_rgba_f(r, g, b, 0);

    al_draw_filled_rectangle(info_start_x + 43 + column,
                             info_start_y + 5 + ypos,
                             info_start_x + 43 + square_side + column,
                             info_start_y + 5 + square_side + ypos, bg);
    
    if (aliens[i].status == RUNNING){
      int energy = aliens[i].energy;
      char energy_c[10];
      sprintf(energy_c, "%d", energy);
      int remaining_energy = aliens[i].remaining_energy;
      char remaining_energy_c[10];
      sprintf(remaining_energy_c, "%d", remaining_energy);
      int period = aliens[i].period;
      char period_c[10];
      sprintf(period_c, "%d", period);
      al_draw_textf(font, al_map_rgba(255, 255, 255, 0),
                    info_start_x + 130 + column, info_start_y + ypos,
                    ALLEGRO_ALIGN_CENTER, "%s/%s", remaining_energy_c, energy_c);
      al_draw_textf(font, al_map_rgba(255, 255, 255, 0),
                    info_start_x + 218 + column, info_start_y + ypos,
                    ALLEGRO_ALIGN_CENTER, "%s", period_c);
    
    } else if (aliens[i].status == TERMINATED){
      al_draw_text(font, al_map_rgba(255, 255, 255, 0),
                    info_start_x + 174 + column, info_start_y + ypos,
                    ALLEGRO_ALIGN_CENTER, "TERMINATED");
    }else{
      al_draw_text(font, al_map_rgba(255, 255, 255, 0),
                    info_start_x + 174 + column, info_start_y + ypos,
                    ALLEGRO_ALIGN_CENTER, "NOT INITIALIZED");
    }


    // Check the row and create new column
    if (i == max_rows) {
      xcol = xcol + 1;
      column = xcol * 280;
      ypos = 0;
      max_rows += 20;
      bg = al_map_rgba(255, 255, 255, 0);
      al_draw_line(info_start_x + 280 + column, 15, info_start_x + 280 + column,
                   maze_width * square_side + 15, bg, 2);
      al_draw_text(font, al_map_rgba(255, 255, 255, 0),
                   info_start_x + 25 + column, 10, ALLEGRO_ALIGN_LEFT, "Alien");
      al_draw_text(font, al_map_rgba(255, 255, 255, 0),
                   info_start_x + 95 + column, 10, ALLEGRO_ALIGN_LEFT,
                   "Energy");
      al_draw_text(font, al_map_rgba(255, 255, 255, 0),
                   info_start_x + 185 + column, 10, ALLEGRO_ALIGN_LEFT,
                   "Period");
    } else {
      ypos += 30;
    }
  }
}

void show_time(int time, ALLEGRO_FONT *font) {
  char time_c[5];
  sprintf(time_c, "%d", time);
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), 215, 640,
               ALLEGRO_ALIGN_LEFT, "Elapsed Time:");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), 380, 640,
               ALLEGRO_ALIGN_LEFT, time_c);
}

void show_aliens(alien aliens[], int maze_start_x, int maze_start_y,
                 int square_side) {
  ALLEGRO_COLOR bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0);
  for (int i = 0; i < alien_amount; ++i) {
    bg = al_map_rgb_f(aliens[i].r, aliens[i].g, aliens[i].b);
    al_draw_filled_rectangle(
        maze_start_x + aliens[i].x * square_side,
        maze_start_y + aliens[i].y * square_side,
        maze_start_x + aliens[i].x * square_side + square_side,
        maze_start_y + aliens[i].y * square_side + square_side, bg);
  }
}

void show_overflow(ALLEGRO_FONT *font, int overflow){
  if (overflow){
  al_draw_text(font, al_map_rgba(255, 0, 0, 0), 215,
        670, ALLEGRO_ALIGN_LEFT, "OVERFLOW!: Processes cannot be scheduled, execution finished");
  }
}

void check_mouse_click(ALLEGRO_MOUSE_STATE mouse_state, toolbar_info toolbar,
                       int *click_wait, int *running, int *manual, int *overflow,
                       algorithm *current_algorithm,
                       input_box *currently_selected, int *time, alien aliens[], char period[], char energy[],
                       char* maze, int maze_height, int maze_width) {

  if (*click_wait == 0) {
    if (al_mouse_button_down(&mouse_state, 1)) {
      *click_wait = 1;
      //  Mouse Clicked.
      int mouse_x = mouse_state.x;
      int mouse_y = mouse_state.y;

      //_____ Check if a button had been clicked: ____
      // Check Switch Mode Button:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_switch &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_switch + toolbar.button_height) {
        // printf("SWITCH Button pressed\n");
        if (!time && !*running)
          button_action_switch(manual);
      }
      // Check Switch Algorithm Button:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_switch_algo &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_switch_algo + toolbar.button_height) {
        // printf("SWITCH Button pressed\n");
        if (!time && !*running)
          button_action_switch_algorithm(current_algorithm);
      }
      // Check Energy Input Box:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_input1 &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_input1 + toolbar.button_height) {
        // printf("Energy Button pressed\n");
        *currently_selected = ENERGY;
      }
      // Check Period Input Box:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_input2 &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_input2 + toolbar.button_height) {
        // printf("Period Button pressed\n");
        *currently_selected = PERIOD;
      }
      // Check Add Button:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_add &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_add + toolbar.button_height) {
        // printf("Add Button pressed\n");

        if (!time || *manual)
          button_action_add(aliens, *running, period, *time, energy, maze, maze_height, maze_width);

      }
      // Check Start/Stop Button:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_start &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_start + toolbar.button_height) {
        // printf("Start Button pressed\n");
        button_action_start(running);
      }
      // Check Reset Button:
      if (mouse_x >= toolbar.x_base && mouse_y >= toolbar.ycoord_reset &&
          mouse_x <= toolbar.x_base + toolbar.button_width &&
          mouse_y <= toolbar.ycoord_reset + toolbar.button_height) {
          button_action_restart(aliens, running ,overflow, time);
      }
    }
  } else {
    if (!al_mouse_button_down(&mouse_state, 1)) {
      *click_wait = 0;
    }
  }
}

void handle_keyboard_press(ALLEGRO_EVENT event, input_box currently_selected,
                           char *energy_text, char *period_text) {
  if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
    int newkey = event.keyboard.unichar;
    char ASCII = newkey & 0xff;
    printf("Just received: %c\n", ASCII);
    char scancode = event.keyboard.keycode;
    if (scancode == ALLEGRO_KEY_BACKSPACE) {
      if (currently_selected == ENERGY) {
        if (strlen(energy_text) > 0)
          energy_text[strlen(energy_text) - 1] = '\0';
      } else {
        if (strlen(period_text) > 0)
          period_text[strlen(period_text) - 1] = '\0';
      }
    }
    if (newkey > 47 && newkey < 58) {
      if (currently_selected == ENERGY)
        strncat(energy_text, &ASCII, 1);
      else
        strncat(period_text, &ASCII, 1);
    }
  }
}


int execute_step(alien aliens[],int time, const char *maze, int maze_width,
                  int maze_height, algorithm current_algorithm) {
  int state = 1; 
  // Check for deadlines, overflow and restore energy (1 = overflow)
  int scheduler_overflow = deadline_check(aliens, alien_amount, time);

  if (scheduler_overflow == 1){
    //Terminate Execution!!!
    state = -1;
  } else {
    // Find alien to move
    alien *current_alien =
        schedule_alien(aliens, alien_amount, current_algorithm);

    if (current_alien != NULL) {
      directions available_directions = get_available_directions(
          maze, maze_width, maze_height, current_alien->x, current_alien->y);
      move_alien(current_alien, available_directions);
      current_alien->remaining_energy--;
    }
  }
  //State: 1 -> success, -1 -> Stop program
  return state;
}

int main(int argc, char *argv[]) {
  alien aliens[max_alien_amount];
  toolbar_info toolbar;
  algorithm current_algorithm = RMS;
  input_box currently_selected = ENERGY;

  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_FONT *font = NULL;
  ALLEGRO_MOUSE_STATE mouse_state;
  bool32 running = 1;
  bool32 manual = 1;
  bool32 redraw = 1;

  int frames = 0;
  int aliens_running = 0;
  int time = 0;
  int overflow = 0;
  int toolbar_width = 200;
  int square_side = 20;
  int graphic_maze_start_x = toolbar_width + 15;
  int graphic_maze_start_y = 15;
  int maze_width, maze_height, info_start_x, info_start_y;
  int info_space;
  int click_wait = 0;
  char *maze;
  maze_width = 31;
  maze_height = 31;
  info_start_x = graphic_maze_start_x + maze_width * square_side + 40;
  info_start_y = 40;
  info_space = 20;
  char energy_text[16] = "";
  char period_text[16] = "";
  //  Allocate the maze array.
  maze = (char *)malloc(maze_width * maze_height * sizeof(char));
  if (maze == NULL) {
    printf("error: not enough memory\n");
    exit(EXIT_FAILURE);
  }
  GenerateMaze(maze, maze_width, maze_height);

  initialize_aliens(aliens, max_alien_amount);

  //  Initialize toolbar info.
  initialize_toolbar(&toolbar);

  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();

  if (al_init()) {
    font = al_load_ttf_font("graphic/roboto.ttf", 24, 0);
    timer = al_create_timer(1.0 / FPS);
    display = al_create_display(screen_width, screen_height);
    event_queue = al_create_event_queue();
    al_install_keyboard();
    al_install_mouse();

    // Register events.
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_set_window_title(display, "Maze");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (running) {
      ALLEGRO_EVENT event;
      al_wait_for_event(event_queue, &event);

      switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
          running = 0;
        } break;
        case ALLEGRO_EVENT_TIMER: {
          // Handles Execution Time
          redraw = 1;
          if (aliens_running == 1) {
            frames++;
            if (frames >= 30) {
              frames = 0;

              if (execute_step(aliens, time, maze, maze_width, maze_height, current_algorithm) != 1){
                //Overflow detected
                aliens_running = 0;
                overflow = 1;
              }
              time+=1;
            }
          }
        } break;
        case ALLEGRO_EVENT_KEY_CHAR:  // fall through
          // case ALLEGRO_EVENT_KEY_UP:   // fall through
          // case ALLEGRO_EVENT_KEY_DOWN:
          {
            handle_keyboard_press(event, currently_selected, energy_text,
                                  period_text);
          }
          break;
        default:
          break;
      }

      //  Check the mouse state.
      al_get_mouse_state(&mouse_state);
      check_mouse_click(mouse_state, toolbar, &click_wait, &aliens_running,
      &manual, &overflow, &current_algorithm, &currently_selected, &time, aliens, period_text, energy_text, maze, maze_height, maze_width);


      if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = 0;

        //  _________ Erase All ________
        al_clear_to_color(al_map_rgb(0, 0, 0));

        //  ________ Show Toolbar ______
        show_toolbar(toolbar, font, maze_width, square_side, manual,
                     aliens_running, current_algorithm, currently_selected,
                     energy_text, period_text);

        //  _________ Maze Draw _________
        show_maze(maze, maze_width, maze_height, graphic_maze_start_x,
                  graphic_maze_start_y, square_side);
        show_aliens(aliens, graphic_maze_start_x, graphic_maze_start_y,
                    square_side);

        //  _________ Time Draw _________
        show_time(time, font);

        //  _________ Oveflow Alert Draw _________
        show_overflow(font, overflow);

        //  _________ Info Draw _________
        show_alien_info(aliens, info_start_x, info_start_y, maze_width,
                        square_side, &info_space, display, font);

        //  __________ Display ___________
        al_flip_display();
      }
    }

    // al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

  } else {
    // TODO log allegro initialization failed
  }

  return 0;
}
