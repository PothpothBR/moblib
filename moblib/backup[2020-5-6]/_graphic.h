#pragma once


#include "_data.h"



// para parte grafica
class _graphic {
public:

	_display display;
	_sourceEvents sourceEvents;
	_data data;

	// bandeira de parada da rotina do programa
	
	bool mouse_is_pressed = false;
	bool endGame = false;

	_graphic() {
		// inserido aqui pois nessecita do <display.screen>
		al_register_event_source(sourceEvents.queue, al_get_display_event_source(display.screen));
	}

	void events() {
		//espera por eventos de mouse e os outros separados
		al_wait_for_event(sourceEvents.queue, &sourceEvents.ev);
		al_get_next_event(sourceEvents.mouse_queue, &sourceEvents.mouse_ev);

		//procesa eventos de mouse
		switch (sourceEvents.mouse_ev.type) {
		case ALLEGRO_EVENT_MOUSE_AXES:
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			break;
		}

		// processar as outras entradas de eventos
		switch (sourceEvents.ev.type) {

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			endGame = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			switch (sourceEvents.ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				endGame = true;
				break;
			case ALLEGRO_KEY_W:
				break;
			case ALLEGRO_KEY_S:
				break;
			case ALLEGRO_KEY_A:
				break;
			case ALLEGRO_KEY_D:
				break;
			}
			break;

		case ALLEGRO_EVENT_KEY_UP:
			switch (sourceEvents.ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				break;
			case ALLEGRO_KEY_S:
				break;
			case ALLEGRO_KEY_A:
				break;
			case ALLEGRO_KEY_D:
				break;
			}
			break;
		}
	}

};