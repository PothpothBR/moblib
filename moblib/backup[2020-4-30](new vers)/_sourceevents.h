#pragma once

#include "_display.h"

class  _sourceEvents {
public:

	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT mouse_ev;
	ALLEGRO_EVENT_QUEUE* queue = nullptr;
	ALLEGRO_EVENT_QUEUE* mouse_queue = nullptr;
	ALLEGRO_TIMER* timer = nullptr;

	_sourceEvents() {
		al_install_keyboard();
		al_install_mouse();

		queue = al_create_event_queue();
		mouse_queue = al_create_event_queue();
		timer = al_create_timer(0.016);

		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_timer_event_source(timer));
		al_register_event_source(mouse_queue, al_get_mouse_event_source());
	}



	~_sourceEvents() {
		al_destroy_event_queue(queue);
		al_destroy_event_queue(mouse_queue);
		al_destroy_timer(timer);
	}
};