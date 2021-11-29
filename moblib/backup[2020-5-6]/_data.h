#pragma once

#include "_sourceevents.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// para a parte de dados gráficos
class _data {
public:
	// define as classes
	

	_data() {
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		// inicia as classes
		
	}

	~_data() {
		// destroi as classes
		
	}

};