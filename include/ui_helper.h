#ifndef UI_HELPER_H_
#define UI_HELPER_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>



typedef struct toolbar_info {
  int y_base, x_base;
  int button_width, button_height;
  int toolbar_width;
  int ycoord_switch, ycoord_switch_algo, ycoord_input1, ycoord_input2;
  int ycoord_add, ycoord_start, ycoord_reset;
} toolbar_info;

typedef enum input_box { ENERGY, PERIOD } input_box;

void initialize_toolbar(toolbar_info *toolbar_info);
void draw_button(ALLEGRO_FONT *font, ALLEGRO_COLOR color, char *label, int x,
                 int y, int width, int height);

void draw_input_box(ALLEGRO_FONT *font, char *content, int x, int y, int width,
                    int height, input_box identifier,
                    input_box currently_selected);


#endif //UI_HELPER_H_