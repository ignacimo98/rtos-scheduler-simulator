#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "alien.h"
#include "maze.h"

const real32 FPS = 60.0f;
const int32 screen_width = 965;
const int32 screen_height = 800;
const real32 move_speed = 2.0f;

const int alien_amount = 5;
ALLEGRO_COLOR bg;

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

int main(int argc, char *argv[]) {
  alien aliens[alien_amount];
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_FONT *font = NULL;
  bool32 running = 1;
  bool32 redraw = 1;
  int32 square_side = 20;
  int32 graphic_maze_start_x = 15;
  int32 graphic_maze_start_y = 15;
  int32 x = 10;
  int32 y = 10;
  int maze_width, maze_height, info_start_x, info_start_y ;
  char *maze;

  maze_width = 31;
  maze_height = 31;
  info_start_x = maze_width*square_side+40;
  info_start_y = 40;

  /* Allocate the maze array. */
  maze = (char *)malloc(maze_width * maze_height * sizeof(char));
  if (maze == NULL) {
    printf("error: not enough memory\n");
    exit(EXIT_FAILURE);
  }
  GenerateMaze(maze, maze_width, maze_height);
  for (int i = 0; i < alien_amount; ++i) {
    initialize_alien(&aliens[i], 10, 0, 2);
  }

  al_init_primitives_addon();

  al_init_font_addon();

  al_init_ttf_addon();

  if (al_init()) {
    font = al_load_ttf_font("graphic/roboto.ttf", 24, 0);
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
            default: {
              directions available_directions = get_available_directions(
                  maze, maze_width, maze_height, aliens[0].x, aliens[0].y);
              move_alien(&aliens[0], available_directions);
            }
            // does nothing
            break;
          }
        } break;
        default:
          break;
      }

      if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = 0;

        al_clear_to_color(al_map_rgb(0, 0, 0));

        //_________ Maze Draw _________
        bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0.5f);
        al_draw_filled_rectangle(x, y, x + square_side, y + square_side, bg);

        show_maze(maze, maze_width, maze_height, graphic_maze_start_x,
                  graphic_maze_start_y, square_side);
        show_aliens(aliens, graphic_maze_start_x, graphic_maze_start_y,
                    square_side);

        //_________ Info Draw _________
        //Separation Line
        bg = al_map_rgba(255, 255, 255, 0);
        al_draw_line(info_start_x, 15, info_start_x, maze_width*square_side+15, bg, 2);
        al_draw_line(info_start_x+280, 15, info_start_x+280, maze_width*square_side+15, bg, 2);

        //Column headers
        al_draw_text(font, al_map_rgba(255, 255, 255, 0), info_start_x+25, 10,
                     ALLEGRO_ALIGN_LEFT, "Alien");
        al_draw_text(font, al_map_rgba(255, 255, 255, 0), info_start_x+95, 10,
                     ALLEGRO_ALIGN_LEFT, "Energy");
        al_draw_text(font, al_map_rgba(255, 255, 255, 0), info_start_x+185, 10,
                     ALLEGRO_ALIGN_LEFT, "Period");

        //Alien information deployment
        for (int i = 0; i < 600; i+= 30){


          bg = al_map_rgba(255, 255, 255, 0);
          al_draw_filled_rectangle(info_start_x+43, info_start_y+5+i, info_start_x+43+square_side, info_start_y+5+square_side+i, bg);
          al_draw_textf(font, al_map_rgba(255, 255, 255, 0), info_start_x+130, info_start_y+i,
                      ALLEGRO_ALIGN_CENTER, "%s/%s","2","3");
          al_draw_textf(font, al_map_rgba(255, 255, 255, 0), info_start_x+218, info_start_y+i,
                      ALLEGRO_ALIGN_CENTER, "%s","10");
        }
        //_________ Display ___________
        al_flip_display();

        x = x >= screen_width ? 0 : x;
        y = y >= screen_height ? 0 : y;
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
