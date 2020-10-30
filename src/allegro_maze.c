#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "alien.h"
#include "maze.h"
#include "ui_helper.h"

const real32 FPS = 60.0f;
const int32 screen_width = 1200;
const int32 screen_height = 800;
const real32 move_speed = 2.0f;

const int alien_amount = 42;
ALLEGRO_COLOR bg;

void button_action_switch(int *manual){
  if (*manual == 1) *manual = 0;
  else *manual = 1;
}
void button_action_add(){
  //oh lord please do something
}
void button_action_start(int *running){
  if (*running == 1) *running = 0;
  else *running = 1;
}
void button_action_restart(){
  //cmon you too?
}

/* Display the maze. */
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

void show_toolbar(toolbar_info toolbar, ALLEGRO_FONT *font, 
                  int maze_width, int square_side, 
                  bool32 manual, bool32 running){
  
  //_____________DRAW VERTICAL LINE
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.toolbar_width, 15, toolbar.toolbar_width, 
              maze_width * square_side + 15,bg, 2);
 
  //_____________DRAW MODE
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base, toolbar.y_base,
               ALLEGRO_ALIGN_LEFT, "Mode:");
  if (manual == 1){
    al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base+80, toolbar.y_base,
               ALLEGRO_ALIGN_LEFT, "Manual");
  }else{
    al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base+80, toolbar.y_base,
               ALLEGRO_ALIGN_LEFT, "Auto");
  }
  //_____________DRAW SWITCH BUTTON
  draw_button(font, al_map_rgba(100, 100, 255, 255), "SWITCH", toolbar.x_base, 
              toolbar.ycoord_switch, toolbar.button_width, toolbar.button_height);

  //_____________DRAW SEPARATION LINE 1
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.x_base,toolbar.y_base+110,toolbar.toolbar_width -20,
              toolbar.y_base+110,bg,2);

  //_____________NEW ALIEN INPUTS AND ADD BUTTON
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base+5, toolbar.y_base+130,
               ALLEGRO_ALIGN_LEFT, "- NEW ALIEN -");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base, toolbar.y_base+170,
               ALLEGRO_ALIGN_LEFT, "ENERGY:");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base, toolbar.ycoord_input1,
               ALLEGRO_ALIGN_LEFT, "-- input1 --");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base, toolbar.y_base+270,
               ALLEGRO_ALIGN_LEFT, "PERIOD:");
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), toolbar.x_base, toolbar.ycoord_input2,
               ALLEGRO_ALIGN_LEFT, "-- input2 --");
  draw_button(font, al_map_rgba(100, 100, 255, 255), "+", toolbar.x_base, 
              toolbar.ycoord_add,toolbar.button_width, toolbar.button_height);

  //_____________DRAW SEPARATION LINE 2
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.x_base,toolbar.y_base+450,toolbar.toolbar_width -20,
              toolbar.y_base+450,bg,2);

  //_____________DRAW START/STOP BUTTON
  if (running){
    draw_button(font, al_map_rgba(247, 7, 30, 255), "STOP", toolbar.x_base, 
                toolbar.ycoord_start, toolbar.button_width, toolbar.button_height);
  }else{
    draw_button(font, al_map_rgba(72, 237, 11, 255), "START", toolbar.x_base, 
                toolbar.ycoord_start, toolbar.button_width, toolbar.button_height);
  }

  //_____________DRAW SEPARATION LINE 3
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar.x_base,toolbar.y_base+574,toolbar.toolbar_width -20,
              toolbar.y_base+574,bg,2);

  //_____________DRAW RESET BUTTON
  draw_button(font, al_map_rgba(247, 7, 30, 255), "RESET", toolbar.x_base, 
              toolbar.ycoord_reset, toolbar.button_width, toolbar.button_height-20);
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

void check_mouse_click(ALLEGRO_MOUSE_STATE mouse_state, toolbar_info toolbar, 
                      int *click_wait, int *running, int *manual){

  if(*click_wait == 0){
    if(al_mouse_button_down(&mouse_state,1)){
      *click_wait = 1;
      //  Mouse Clicked.
      int mouse_x = mouse_state.x;
      int mouse_y = mouse_state.y;
      //printf("mouse in %d\n",mouse_x);

      //_____ Check if a button had been clicked: ____
      //Check Switch Button:
      if (mouse_x >= toolbar.x_base 
        && mouse_y >= toolbar.ycoord_switch 
        && mouse_x <=toolbar.x_base + toolbar.button_width  
        && mouse_y <= toolbar.ycoord_switch+toolbar.button_height){
          printf("SWITCH Button pressed\n");
          button_action_switch(manual);
      }
      //Check Add Button:
      if (mouse_x >= toolbar.x_base 
        && mouse_y >= toolbar.ycoord_add
        && mouse_x <=toolbar.x_base + toolbar.button_width  
        && mouse_y <= toolbar.ycoord_add+toolbar.button_height){
          printf("Add Button pressed\n");
          button_action_add();
        }
      //Check Start/Stop Button:
      if (mouse_x >= toolbar.x_base 
        && mouse_y >= toolbar.ycoord_start
        && mouse_x <=toolbar.x_base + toolbar.button_width  
        && mouse_y <= toolbar.ycoord_start+toolbar.button_height){
          printf("Start Button pressed\n");
          button_action_start(running);
        }
      //Check Reset Button:
      if (mouse_x >= toolbar.x_base 
        && mouse_y >= toolbar.ycoord_reset
        && mouse_x <=toolbar.x_base + toolbar.button_width  
        && mouse_y <= toolbar.ycoord_reset+toolbar.button_height-20){
          printf("Restart Button pressed\n");
          button_action_restart();
        }
    }
  } else {
    if(!al_mouse_button_down(&mouse_state,1)){
      *click_wait=0;
    }
  }
}

void show_alien_info(alien aliens[], int info_start_x, int info_start_y,
                     int maze_width, int square_side, int* info_space,
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

    int energy = aliens[i].energy;
    char energy_c[10];
    sprintf(energy_c, "%d", energy);
    int remaining_energy = aliens[i].remaining_energy;
    char remaining_energy_c[10];
    sprintf(remaining_energy_c, "%d", remaining_energy);
    int period = aliens[i].period;
    char period_c[10];
    sprintf(period_c, "%d", period);

    al_draw_filled_rectangle(info_start_x + 43 + column,
                             info_start_y + 5 + ypos,
                             info_start_x + 43 + square_side + column,
                             info_start_y + 5 + square_side + ypos, bg);
    al_draw_textf(font, al_map_rgba(255, 255, 255, 0),
                  info_start_x + 130 + column, info_start_y + ypos,
                  ALLEGRO_ALIGN_CENTER, "%s/%s", remaining_energy_c, energy_c);
    al_draw_textf(font, al_map_rgba(255, 255, 255, 0),
                  info_start_x + 218 + column, info_start_y + ypos,
                  ALLEGRO_ALIGN_CENTER, "%s", period_c);
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

void execute_step(alien aliens[], const char *maze, int maze_width,
                  int maze_height) {
  directions available_directions = get_available_directions(
      maze, maze_width, maze_height, aliens[0].x, aliens[0].y);
  move_alien(&aliens[0], available_directions);
}

int main(int argc, char *argv[]) {
  alien aliens[alien_amount];
  toolbar_info toolbar;
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_FONT *font = NULL;
  ALLEGRO_MOUSE_STATE mouse_state;
  bool32 running = 1;
  bool32 manual = 1; 
  bool32 redraw = 1;
  int32 x = 10;
  int32 y = 10;
  int frames = 0;
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
  

  //  Allocate the maze array.
  maze = (char *)malloc(maze_width * maze_height * sizeof(char));
  if (maze == NULL) {
    printf("error: not enough memory\n");
    exit(EXIT_FAILURE);
  }
  GenerateMaze(maze, maze_width, maze_height);

  for (int i = 0; i < alien_amount; ++i) {
    initialize_alien(&aliens[i], 10, 0, 2);
  }
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
          redraw = 1;
          frames++;
          if (frames >= 30) {
            frames = 0;
            execute_step(aliens, maze, maze_width, maze_height);
          }

        } break;
        // case ALLEGRO_EVENT_KEY_CHAR: // fall through
        // case ALLEGRO_EVENT_KEY_UP:   // fall through
        case ALLEGRO_EVENT_KEY_DOWN: {
          switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_W: {
              y -= square_side;
            } break;
            case ALLEGRO_KEY_S: {
              y += square_side;
            } break;
            case ALLEGRO_KEY_A: {
              x -= square_side;
            } break;
            case ALLEGRO_KEY_D: {
              x += square_side;
            } break;
            default:
              // does nothing
              break;
          }
        } break;
        default:
          break;
      }

      //  Check the mouse state.
      al_get_mouse_state(&mouse_state);
      check_mouse_click(mouse_state, toolbar, &click_wait, &running, &manual);

      if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = 0;

        //  _________ Erase All ________
        al_clear_to_color(al_map_rgb(0, 0, 0));
        
        //  ________ Show Toolbar ______
        show_toolbar(toolbar, font, maze_width, square_side, manual, running);

        //  _________ Maze Draw _________
        // bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0.5f);
        // al_draw_filled_rectangle(x, y, x + square_side, y + square_side, bg);

        show_maze(maze, maze_width, maze_height, graphic_maze_start_x,
                  graphic_maze_start_y, square_side);
        show_aliens(aliens, graphic_maze_start_x, graphic_maze_start_y,
                    square_side);

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
