#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "maze.h"

const real32 FPS = 60.0f;
const int32 screen_width = 800;
const int32 screen_height = 600;
const real32 move_speed = 2.0f;
ALLEGRO_COLOR bg;

/* Display the maze. */
void ShowMaze(const char *maze, int width, int height) {
  int x, y;
  bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0);
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      switch (maze[y * width + x]) {
        case 1:
          al_draw_filled_rectangle(x*10, y*10, x+10 + 10, y+10 + 10, bg);
          break;
        case 2:
          break;
        default:
          break;
      }
    }
    // printf("\n");
  }
}

int main(int argc, char *argv[]) {
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_FONT *font = NULL;
  bool32 running = 1;
  bool32 redraw = 1;

  int32 square_side = 10;

  int32 x = 10;
  int32 y = 10;

  int maze_width, maze_height;
  char *maze;
  maze_width = 21;
  maze_height = 21;
  /* Allocate the maze array. */
  maze = (char *)malloc(maze_width * maze_height * sizeof(char));
  if (maze == NULL) {
    printf("error: not enough memory\n");
    exit(EXIT_FAILURE);
  }
  GenerateMaze(maze, maze_width, maze_height);

  al_init_primitives_addon();
  al_init_ttf_addon();
  al_init_font_addon();

  if (al_init()) {
    timer = al_create_timer(1.0 / FPS);
    display = al_create_display(screen_width, screen_height);
    al_install_keyboard();
    event_queue = al_create_event_queue();

    // register events
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
          // does nothing ?
          break;
      }

      if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = 0;

        //Erase (?)
        al_clear_to_color(al_map_rgb(0,0,0));

       
        font = al_load_ttf_font ("graphic/roboto.ttf" , 24,0);
        al_draw_text(font, al_map_rgba(255,255,255,0) , 100 , 10 , ALLEGRO_ALIGN_RIGHT , "ENERGY: ");

        //Draw energy indicator
        bg = al_map_rgba(255,255,255,255);
        al_draw_filled_rectangle(100, 10, 300, 30, bg);

        bg = al_map_rgba(247,243,7,255);
        al_draw_filled_rectangle(101, 11, 299, 29, bg);

    
        //Draw
        bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0);
        al_draw_filled_rectangle(x, y, x + square_side, y + square_side, bg);
        
        // ShowMaze(maze, maze_width, maze_height);
        
        //Draw everything on Screen
        al_flip_display();

        x = x >= screen_width ? 0 : x;
        y = y >= screen_height ? 0 : y;
      }
    }

    //al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

  } else {
    // TODO log allegro initialization failed
  }

  return 0;
}
