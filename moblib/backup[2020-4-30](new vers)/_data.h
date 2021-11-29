#pragma once

#include "_sourceevents.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class _data {
public:

	ALLEGRO_BITMAP* playersheet = nullptr;
	ALLEGRO_BITMAP* tilemap = nullptr;
	ALLEGRO_FONT* fonte16 = nullptr;

	_data() {
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		
		fonte16 = al_load_ttf_font("serifa-light.ttf", 16, NULL);
		playersheet = al_load_bitmap("pers.png");
		tilemap = al_load_bitmap("anima1-0.png");
	}

	~_data() {
		al_destroy_font(fonte16);
		al_destroy_bitmap(playersheet);
		al_destroy_bitmap(tilemap);
	}

};