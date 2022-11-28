#include <iostream>
#include <math.h>
using namespace std;

#include <allegro5/allegro.h>

#include "graphic/lastest/graphic.h"
#include "graphic/lastest/colors.h"
#include "../../moblib/moblib4.h"


int main() {

	

	MOB_MAPPING map(new MOB_POSITION(-32, 0), new MOB_SHEET(32 * 4, 32 * 4, 4, 4), 32, 32, graphic.screen_x-32, graphic.screen_y - 32);
	MOB_MOVIMENT::KEYBOARD<MOB_POSITION> keyboard_pos(map.position, 4);
	mob_load_map(&map, "mapa.txt");
	MOB_COLLISION::COLID centerobj(new MOB_POSITION(graphic.screen_x / 2 - 32, graphic.screen_y / 2 - 32),  new MOB_DIMENSION(40, 40));




	MOB_COLLISION::COLID otrobj(new MOB_POSITION(graphic.screen_x / 2 + 90, graphic.screen_y / 2 + 160), new MOB_DIMENSION(60, 60));
	MOB_MOVIMENT::KEYBOARD<MOB_POSITION> keyboard_pos2(otrobj.form.position, 10);

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

			if (graphic.keyboard_press()) {
				if (graphic.keyboard_input() == 'w') {
					keyboard_pos2.UP = true;
				}
				else if (graphic.keyboard_input() == 'a') {
					keyboard_pos2.LEFT = true;
				}
				else if (graphic.keyboard_input() == 's') {
					keyboard_pos2.DOWN = true;
				}
				else if (graphic.keyboard_input() == 'd') {
					keyboard_pos2.RIGHT = true;
				}
			}

			else if (!graphic.keyboard_press()) {
				if (graphic.keyboard_input() == 'w') {
					keyboard_pos2.UP = false;
				}
				else if (graphic.keyboard_input() == 'a') {
					keyboard_pos2.LEFT = false;
				}
				else if (graphic.keyboard_input() == 's') {
					keyboard_pos2.DOWN = false;
				}
				else if (graphic.keyboard_input() == 'd') {
					keyboard_pos2.RIGHT = false;
				}
			}

			mob_run(&keyboard_pos);
			mob_reload_collision(&otrobj);
			mob_run(&keyboard_pos2);
			mob_reload_colision_mirror(&keyboard_pos, &centerobj);
			//mob_collision(&otrobj, &centerobj.form, 1);
			//mob_collision_mirror(&otrobj, centerobj.form.position->x, centerobj.form.position->y, centerobj.form.dimension->width, centerobj.form.dimension->height, otrobj.form.position);
		}


		for (MOB_FORM_CHAIN* ptr = map.rectangle_list; ptr; ptr = ptr->next) {
			float mapx = mob_map_position_x(&map, ptr);
			float mapy = mob_map_position_y(&map, ptr);
			float maph = ptr->form.dimension->height, mapw = ptr->form.dimension->width;
			float gx = centerobj.form.position->x, gy = centerobj.form.position->y;
			mob_collision_mirror(&centerobj, mapx, mapy, mapw, maph, map.position, false);
		
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
			al_draw_rectangle(mapx, mapy, mapx + mapw, mapy + maph, black, 4);
		}
		al_draw_rectangle(otrobj.form.position->x, otrobj.form.position->y, otrobj.form.position->x + otrobj.form.dimension->width, otrobj.form.position->y + otrobj.form.dimension->height, black, 1);
		al_draw_rectangle(otrobj.trail.x, otrobj.trail.y, otrobj.trail.x + otrobj.form.dimension->width, otrobj.trail.y + otrobj.form.dimension->height, red, 1);

		

		al_draw_rectangle(centerobj.form.position->x, centerobj.form.position->y, centerobj.form.position->x + centerobj.form.dimension->width, centerobj.form.position->y + centerobj.form.dimension->height, blue, 1);
		al_draw_rectangle(centerobj.trail.x, centerobj.trail.y, centerobj.trail.x + centerobj.form.dimension->width, centerobj.trail.y + centerobj.form.dimension->height, red, 1);
	}

	return 0;
}