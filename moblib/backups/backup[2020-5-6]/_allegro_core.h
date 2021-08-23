#pragma once

#include "_graphic.h"
#include "_colors.h"

namespace _allegro_ {
	// nucleo do programa
	class _Core {
	public:
		_graphic graphic;

		// junta as 3 classes <_frontEnd | _backEnd | _tempCache> iniciando-as
		_Core() {
			al_start_timer(graphic.sourceEvents.timer);
		}

		// retorna se a execucao sera timed e coleta os eventos
		bool timedExecution() {
			graphic.events();
			return (graphic.sourceEvents.ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(graphic.sourceEvents.queue));
		}

		// atualiza a tela e define se o programa continuara
		bool loop() {
			al_flip_display();
			al_clear_to_color(al_map_rgb(22, 24, 28));
			return !graphic.endGame;
		}

	}Core;
}