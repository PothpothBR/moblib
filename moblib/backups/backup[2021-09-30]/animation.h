/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     /  _|             |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/
#ifndef ANIMATION_H
#define ANIMATION_H

#include "timing.h"
 
typedef short int sint;

namespace MOB_ANIM {

	constexpr sint FORWARD = 0;
	constexpr sint BACK = 1;
	constexpr sint FLIP = 2;

	// argumentos: <range_of_cells,  direction, cellInterval, stepCell>
	class INSTANCE {
	public:
		int  direction = 0, range_of_cells = 0, step = 0;
		float delay = 0, FPS = 0;

		INSTANCE(sint range_of_cells, sint direction = 0, float delay = 0, float FPS = 0, sint stepCell = 0) {
			this->direction = direction;
			this->range_of_cells = range_of_cells - 1;
			this->delay = delay;
			this->step = stepCell + 1;
			this->FPS = FPS;
		}

		INSTANCE() {}

	};

	// argumentos: <startCell>
	class ANIMATE {
	public:
		int start, end, index, flip;

		MOB_TICKS* time;

		INSTANCE* instance = nullptr;

		ANIMATE(INSTANCE* instance, sint startCell = 0) {
			this->instance = instance;
			(instance->direction == 2) ? this->index = startCell + 1 : this->index = startCell - 1;
			this->start = startCell;
			this->end = startCell + instance->range_of_cells;
			this->flip = -(instance->step);
			time = new MOB_TICKS(instance->delay, instance->FPS);
		}
		~ANIMATE() {
			delete time;
		}

	};

}

// anima o objeto
int mob_anim(MOB_ANIM::ANIMATE* self) {
	if (!self->time->tick()) {
		return self->index;
	}
	if (self->instance->direction == MOB_ANIM::FORWARD) {
		self->index += self->instance->step;
		if (self->index > self->end) self->index = self->start;
		return self->index;
	}
	else if (self->instance->direction == MOB_ANIM::BACK) {
		self->index -= self->instance->step;
		if (self->index < self->start) self->index = self->end;
		return self->index;
	}
	else if (self->instance->direction == MOB_ANIM::FLIP) {
		if (self->index + self->flip < self->start || self->index + self->flip > self->end) self->flip *= -1;
		self->index += self->flip;
		return self->index;
	}
	return -1;
}

#endif
