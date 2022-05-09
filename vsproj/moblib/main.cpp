#include <iostream>
#include <math.h>
using namespace std;

#include <allegro5/allegro.h>

#include "graphic/lastest/graphic.h"
#include "graphic/lastest/colors.h"
#include "../../moblib/lastest/moblib.h"

int main() {

	

	MOB_MAPPING map(new MOB_POSITION(-32, 0), new MOB_SHEET(32 * 4, 32 * 4, 4, 4), 32, 32, graphic.screen_x-32, graphic.screen_y - 32);
	MOB_MOVIMENT::KEYBOARD<MOB_POSITION> keyboard_pos(map.position, 4);
	mob_load_map(&map, "mapa.txt");
	MOB_COLLISION::COLID centerobj(new MOB_POSITION(graphic.screen_x / 2 - 16, graphic.screen_y / 2 - 16),  new MOB_DIMENSION(32, 32));

	mob_generate_rectangle_map(&map);

	while (graphic.flip()) {
	
		if (graphic.timed()) {
			if (graphic.keyboard_press()) {
				if (graphic.keyboard_input() == 'w') {
					keyboard_pos.DOWN = true;
				}
				else if (graphic.keyboard_input() == 'a') {
					keyboard_pos.RIGHT = true;
				}
				else if (graphic.keyboard_input() == 's') {
					keyboard_pos.UP = true;
				}
				else if (graphic.keyboard_input() == 'd') {
					keyboard_pos.LEFT = true;
				}
			}

			else if(!graphic.keyboard_press()){
				if (graphic.keyboard_input() == 'w') {
					keyboard_pos.DOWN = false;
				}
				else if (graphic.keyboard_input() == 'a') {
					keyboard_pos.RIGHT = false;
				}
				else if (graphic.keyboard_input() == 's') {
					keyboard_pos.UP = false;
				}
				else if (graphic.keyboard_input() == 'd') {
					keyboard_pos.LEFT = false;
				}
			}

			mob_run(&keyboard_pos);
			mob_reload_colision_mirror(&keyboard_pos, &centerobj);
		}
		for (register int y = 0; y < map.map->height; y++) {
			for (register int x = 0; x < map.map->width; x++) {
				if (mob_map_overdraw(&map, x, y)) continue;
				switch (mob_map_cell(map.map, x, y, 0)) {
				case 0:
					al_draw_filled_rectangle(mob_map_position_x(&map, x, y), mob_map_position_y(&map, x, y),
						mob_map_position_x(&map, x, y) + map.sheet->cell_dimension.width, mob_map_position_y(&map, x, y) + map.sheet->cell_dimension.height, white);
					al_draw_rectangle(mob_map_position_x(&map, x, y), mob_map_position_y(&map, x, y),
						mob_map_position_x(&map, x, y) + map.sheet->cell_dimension.width, mob_map_position_y(&map, x, y) + map.sheet->cell_dimension.height, gray, 1);
					break;
				case 1:
					al_draw_filled_rectangle(mob_map_position_x(&map, x, y), mob_map_position_y(&map, x, y),
						mob_map_position_x(&map, x, y) + map.sheet->cell_dimension.width, mob_map_position_y(&map, x, y) + map.sheet->cell_dimension.height, red);
					al_draw_rectangle(mob_map_position_x(&map, x, y), mob_map_position_y(&map, x, y),
						mob_map_position_x(&map, x, y) + map.sheet->cell_dimension.width, mob_map_position_y(&map, x, y) + map.sheet->cell_dimension.height, gray, 1);
					break;
				case 2:
					al_draw_filled_rectangle(mob_map_position_x(&map, x, y), mob_map_position_y(&map, x, y),
						mob_map_position_x(&map, x, y) + map.sheet->cell_dimension.width, mob_map_position_y(&map, x, y) + map.sheet->cell_dimension.height, green);
					al_draw_rectangle(mob_map_position_x(&map, x, y), mob_map_position_y(&map, x, y),
						mob_map_position_x(&map, x, y) + map.sheet->cell_dimension.width, mob_map_position_y(&map, x, y) + map.sheet->cell_dimension.height, gray, 1);
					break;
				}
			}
		}
		for (MOB_FORM_CHAIN* ptr = map.rectangle_list; ptr; ptr = ptr->next) {
			float mapx = mob_map_position_x(&map, ptr);
			float mapy = mob_map_position_y(&map, ptr);
			float maph = ptr->form.dimension->height, mapw = ptr->form.dimension->width;
			float gx = centerobj.form.position->x, gy = centerobj.form.position->y;

			(mob_collision(gx, gy, centerobj.form.dimension->width, centerobj.form.dimension->height, mapx, mapy, mapw, maph))?
				al_draw_rectangle(mapx, mapy, mapx + mapw, mapy + maph, red, 4) :
				al_draw_rectangle(mapx, mapy, mapx + mapw, mapy + maph, black, 4);


			(mob_collision(&centerobj, mapx, mapy, mapw, maph, 1)) ?
				al_draw_rectangle(mapx, mapy, mapx + mapw, mapy + maph, red, 4) : al_draw_rectangle(mapx, mapy, mapx + mapw, mapy + maph, black, 4);

		}
		al_draw_rectangle(centerobj.form.position->x, centerobj.form.position->y, centerobj.form.position->x + 32, centerobj.form.position->y + 32, black, 3);
		al_draw_rectangle(centerobj.trail.x, centerobj.trail.y, centerobj.trail.x + 32, centerobj.trail.y + 32, red, 1);
	}

	return 0;
}