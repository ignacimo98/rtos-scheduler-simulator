#include "maze.h"

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const real32 FPS = 60.0f;
const int32 screen_width = 800;
const int32 screen_height = 600;
const real32 move_speed = 2.0f;

int main(int argc, char *argv[]) {

  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_TIMER *timer = NULL;
  bool32 running = 1;
  bool32 redraw = 1;

  int32 x = 10;
  int32 y = 10;
  
  al_init_primitives_addon();

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
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_start_timer(timer);

    while (running) {
      ALLEGRO_EVENT event;
      al_wait_for_event(event_queue, &event);

      switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
        {
          running = 0;
        } break;
        case ALLEGRO_EVENT_TIMER:
        {
          redraw = 1;
        } break;
        case ALLEGRO_EVENT_KEY_CHAR: // fall through
        //case ALLEGRO_EVENT_KEY_UP:   // fall through
        case ALLEGRO_EVENT_KEY_DOWN:
          {
            switch (event.keyboard.keycode) {
              case ALLEGRO_KEY_W:
                {
                  y -= 2;
                } break;
              case ALLEGRO_KEY_S:
                {
                  y += 2;
                } break;
              case ALLEGRO_KEY_A:
                {
                  x -= 2;
                } break;
              case ALLEGRO_KEY_D:
                {
                  x += 2;
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

      if(redraw && al_is_event_queue_empty(event_queue)) {
        redraw = 0;
        al_clear_to_color(al_map_rgb(0,0,0));
        ALLEGRO_COLOR bg = al_map_rgba_f(1.0f,1.0f,1.0f,0);
        al_draw_filled_rectangle(x, y, x+30, y+30, bg);
        al_flip_display();

        x = x >= screen_width ? 0 : x;
        y = y >= screen_height ? 0 : y;
      }
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

  } else {
    //TODO log allegro initialization failed
  }

  return 0;
}
