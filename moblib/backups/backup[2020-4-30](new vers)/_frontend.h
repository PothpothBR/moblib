#pragma once


#include "_data.h"
#include "_backend.h"


// para parte grafica
class _frontEnd {
public:
	_backEnd backEnd;

	_display display;
	_sourceEvents sourceEvents;
	_data data;

	// bandeira de parada da rotina do programa
	bool endGame = false;
	bool mouse_is_pressed = false;

	_frontEnd() {
		// inserido aqui pois nessecita do <display.screen>
		al_register_event_source(sourceEvents.queue, al_get_display_event_source(display.screen));
	}

	void events() {
		//espera por eventos de mouse e os outros separados
		al_wait_for_event(sourceEvents.queue, &sourceEvents.ev);
		al_get_next_event(sourceEvents.mouse_queue, &sourceEvents.mouse_ev);

		//procesa eventos de mouse
		switch (sourceEvents.mouse_ev.type) {
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			backEnd.player.mouse.x = sourceEvents.mouse_ev.mouse.x;
			backEnd.player.mouse.y = sourceEvents.mouse_ev.mouse.y;
			backEnd.player.mouse_is_pressed = true;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			backEnd.player.mouse_is_pressed = false;
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
				backEnd.player.Player.moviment->activeUP = true;
				break;
			case ALLEGRO_KEY_S:
				backEnd.player.Player.moviment->activeDOWN = true;
				break;
			case ALLEGRO_KEY_A:
				backEnd.player.Player.moviment->activeLEFT = true;
				break;
			case ALLEGRO_KEY_D:
				backEnd.player.Player.moviment->activeRIGHT = true;
				break;
			}

			break;

		case ALLEGRO_EVENT_KEY_UP:
			switch (sourceEvents.ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				backEnd.player.Player.moviment->activeUP = false;
				break;
			case ALLEGRO_KEY_S:
				backEnd.player.Player.moviment->activeDOWN = false;
				break;
			case ALLEGRO_KEY_A:
				backEnd.player.Player.moviment->activeLEFT = false;
				break;
			case ALLEGRO_KEY_D:
				backEnd.player.Player.moviment->activeRIGHT = false;
				break;
			}
			break;
		}
	}

};