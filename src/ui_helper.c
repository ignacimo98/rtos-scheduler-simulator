#include "ui_helper.h"


void draw_button(ALLEGRO_FONT *font,
                 ALLEGRO_COLOR color, char *label, int x, int y, int width,
                 int height) {
  al_draw_filled_rectangle(x, y, x + width, y + height, color);
  al_draw_text(font, al_map_rgba(255, 255, 255, 0),
                  (x+x+width)/2, y,
                  ALLEGRO_ALIGN_CENTER, label);

}
