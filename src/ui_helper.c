#include "ui_helper.h"

void initialize_toolbar(toolbar_info *toolbar_info) {
  toolbar_info->y_base = 10;
  toolbar_info->x_base = 20;
  toolbar_info->button_height = 30;
  toolbar_info->button_width = 160;
  toolbar_info->toolbar_width = 200;
  toolbar_info->ycoord_switch = toolbar_info->y_base + 40;
  toolbar_info->ycoord_switch_algo = toolbar_info->ycoord_switch + 90;
  toolbar_info->ycoord_input1 = toolbar_info->ycoord_switch_algo + 160;
  toolbar_info->ycoord_input2 = toolbar_info->ycoord_input1 +75;
  toolbar_info->ycoord_add = toolbar_info->ycoord_input2+50;
  toolbar_info->ycoord_start = toolbar_info->ycoord_add+90;
  toolbar_info->ycoord_reset = toolbar_info->ycoord_start+90;
}

void draw_button(ALLEGRO_FONT *font, ALLEGRO_COLOR color, char *label, int x,
                 int y, int width, int height) {
  ALLEGRO_COLOR bg = al_map_rgba(255, 255, 255, 0);
  al_draw_filled_rectangle(x, y, x + width, y + height, bg);

  al_draw_filled_rectangle(x + 1, y + 1, x + width - 1, y + height - 1, color);
  al_draw_text(font, al_map_rgba(255, 255, 255, 0), (x + x + width) / 2, y,
               ALLEGRO_ALIGN_CENTER, label);
}

void draw_input_box(ALLEGRO_FONT *font, char *content, int x, int y, int width,
                    int height, input_box identifier,
                    input_box currently_selected) {
  
  if (identifier == currently_selected)
    al_draw_filled_rectangle(x - 1, y - 1, x + width + 1, y + height + 1,
                             al_map_rgba(0, 255, 255, 0));

  al_draw_filled_rectangle(x + 1, y + 1, x + width - 1, y + height - 1,
                           al_map_rgba(255, 255, 255, 0));

  al_draw_text(font, al_map_rgba(0,0,0, 255), (x + x + width) / 2, y,
               ALLEGRO_ALIGN_CENTER, content);
}
