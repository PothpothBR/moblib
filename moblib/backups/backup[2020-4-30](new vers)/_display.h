#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

#include <allegro5/allegro_primitives.h>

class _display {
public:
	ALLEGRO_DISPLAY* screen = nullptr;

	_display() {
		al_init();
		al_init_primitives_addon();
		
		screen = al_create_display(1080, 720);
	}

	~_display() {
		al_destroy_display(screen);
	}

};