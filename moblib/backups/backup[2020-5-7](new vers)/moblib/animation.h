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

#include "debug_log.h"

#define mlANIM_F 0
#define mlANIM_B 1
#define mlANIM_L 2

 
typedef  short int sint;

namespace ANIMATION {
	// argumentos: <rangeOfCells,  direction, cellInterval, stepCell>
	class INSTANCE {
	public:
		sint  direction, rangeOfCells, interval, step;

		INSTANCE(sint rangeOfCells, sint direction = 0, sint cellInterval = 0, sint stepCell = 0) {
			debugLog("created obj <mlAnimationInstance>");
			this->direction = direction;
			this->rangeOfCells = rangeOfCells - 1;
			this->interval = cellInterval + 1;
			this->step = stepCell + 1;

			debugLog("interval: ", interval);
			debugLog("direction: ", direction);
			debugLog("rangeOfCells: ", rangeOfCells);
			debugLog("step: ", step);
		}

	};

	// argumentos: <startCell>
	class ANIMATE {
	public:
		sint start, end, jump, index, flip;

		INSTANCE *stance = nullptr;

		ANIMATE(INSTANCE *stance, sint startCell = 0) {
			debugLog("created obj <mlAnimation>");

			this->stance = stance;

			(stance->direction == 2) ? this->index = startCell + 1 : this->index = startCell - 1;

			this->start = startCell;
			this->end = startCell + stance->rangeOfCells;
			this->jump = 0;
			this->flip = -(stance->step);


			debugLog("index: ", index);
			debugLog("start: ", start);
			debugLog("end: ", end);
			debugLog("jump: ", jump);
			debugLog("flip: ", flip);

		}

	};

	namespace MTH{
		using namespace ANIMATION;
		// anima o objeto
		int anim(ANIMATE *self) {
			if (self->jump > 1) {
				self->jump--;
				return self->index;
			}

			self->jump = self->stance->interval;

			if (self->stance->direction == mlANIM_F) {
				self->index += self->stance->step;
				if (self->index > self->end) self->index = self->start;
				return self->index;
			}
			else if (self->stance->direction == mlANIM_B) {
				self->index -= self->stance->step;
				if (self->index < self->start) self->index = self->end;
				return self->index;
			}
			else if (self->stance->direction == mlANIM_L) {
				if (self->index <= self->start || self->index >= self->end) self->flip *= -1;
				self->index += self->flip;
				return self->index;
			}
			return 0;
		}
	}
}

#endif
