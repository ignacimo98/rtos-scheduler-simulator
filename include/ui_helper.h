#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

typedef struct toolbar_info
{
 int y_base, x_base;
 int button_width, button_height;
 int toolbar_width; 
 int ycoord_switch, ycoord_input1, ycoord_input2;
 int ycoord_add, ycoord_start, ycoord_reset;
} toolbar_info;
void initialize_toolbar(toolbar_info* toolbar_info);
void draw_button(ALLEGRO_FONT *font, ALLEGRO_COLOR color, char *label,
                 int x, int y, int width, int height);


