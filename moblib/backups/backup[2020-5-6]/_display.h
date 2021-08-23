#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

class _display {
public:
	// cria classe da tela
	ALLEGRO_DISPLAY* screen = nullptr;

	_display() {
		// inicia a biblioteca allegro
		al_init();
		al_init_primitives_addon();
		// cria a tela
		screen = al_create_display(1080, 720);
	}

	~_display() {
		// destroi a tela
		al_destroy_display(screen);
	}

};