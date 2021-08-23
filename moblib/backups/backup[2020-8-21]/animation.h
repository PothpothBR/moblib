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

namespace ANIM {

	constexpr sint FORWARD = 0;
	constexpr sint BACK = 1;
	constexpr sint FLIP = 2;

	// argumentos: <rangeOfCells,  direction, cellInterval, stepCell>
	class INSTANCE {
	public:
		int  direction, rangeOfCells,  step;
		float delay, FPS;

		INSTANCE(sint rangeOfCells, sint direction = 0, float delay = 0, float FPS=0, sint stepCell = 0) {
			this->direction = direction;
			this->rangeOfCells = rangeOfCells - 1;
			this->delay = delay ;// "+ 1" ?
			this->step = stepCell + 1;
			this->FPS = FPS;
		}

	};

	// argumentos: <startCell>
	class ANIMATE {
	public:
		int start, end, index, flip;

		TICKS *time;

		INSTANCE *stance = nullptr;

		ANIMATE(INSTANCE *stance, sint startCell = 0) {
			this->stance = stance;
			(stance->direction == 2) ? this->index = startCell + 1 : this->index = startCell - 1;
			this->start = startCell;
			this->end = startCell + stance->rangeOfCells;
			this->flip = -(stance->step);
			time = new TICKS(stance->delay,stance->FPS); // pode dar erro condverso de <p u-int> para <p int>
		}
		~ANIMATE() {
			delete time;
		}

	};

	// anima o objeto
	int anim(ANIMATE *self) {
		if (!self->time->tick()) {
			return self->index;
		}
		if (self->stance->direction == FORWARD) {
			self->index += self->stance->step;
			if (self->index > self->end) self->index = self->start;
			return self->index;
		}
		else if (self->stance->direction == BACK) {
			self->index -= self->stance->step;
			if (self->index < self->start) self->index = self->end;
			return self->index;
		}
		else if (self->stance->direction == FLIP) {
			if (self->index <= self->start || self->index >= self->end) self->flip *= -1;
			self->index += self->flip;
			return self->index;
		}
		return -1;
	}
	
}

#endif
