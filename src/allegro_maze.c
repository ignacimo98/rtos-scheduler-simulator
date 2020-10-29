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

void show_toolbar(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int toolbar_width, int maze_width, int square_side){
  
  bg = al_map_rgba(255, 255, 255, 0);
  al_draw_line(toolbar_width, 15, toolbar_width, maze_width * square_side + 15,
               bg, 2);

  draw_button(font, al_map_rgba_f(0.2f, 0.0f, 0.5f, 0), "caca", 10, 10, 90, 40);
  draw_button(font, al_map_rgba_f(0.5f, 0.0f, 0.2f, 0), "caca1", 100, 10, 90, 40);


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
  int frames = 0;
  alien aliens[alien_amount];
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  ALLEGRO_FONT *font = NULL;
  bool32 running = 1;
  bool32 redraw = 1;

  int toolbar_width = 200;

  int square_side = 20;
  int graphic_maze_start_x = toolbar_width + 15;
  int graphic_maze_start_y = 15;
  int32 x = 10;
  int32 y = 10;

  int maze_width, maze_height, info_start_x, info_start_y;
  int info_space;
  char *maze;

  maze_width = 31;
  maze_height = 31;
  info_start_x = graphic_maze_start_x + maze_width * square_side + 40;
  info_start_y = 40;
  info_space = 20;

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

      if (redraw && al_is_event_queue_empty(event_queue)) {
        redraw = 0;

        al_clear_to_color(al_map_rgb(0, 0, 0));
        // ________ Show Toolbar ______
        show_toolbar(display, font, toolbar_width, maze_width, square_side);

        //_________ Maze Draw _________
        // bg = al_map_rgba_f(1.0f, 1.0f, 1.0f, 0.5f);
        // al_draw_filled_rectangle(x, y, x + square_side, y + square_side, bg);

        show_maze(maze, maze_width, maze_height, graphic_maze_start_x,
                  graphic_maze_start_y, square_side);
        show_aliens(aliens, graphic_maze_start_x, graphic_maze_start_y,
                    square_side);

        // _________ Info Draw _________
        show_alien_info(aliens, info_start_x, info_start_y, maze_width,
                        square_side, &info_space, display, font);
        

        //_________ Display ___________
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
