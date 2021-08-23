/*----------------------------------------------------
  |               Programa feito por                 |
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
  ----------------------------------------------------*/
#ifndef ANIMATION_H
#define ANIMATION_H

#include "debug_log.h"

#define ANIMATION_FORWARD 0
#define ANIMATION_BACK 1
#define ANIMATION_FLIP 2

typedef unsigned short int usint;
typedef  short int sint;

constexpr usint NORMAL = 0;
constexpr usint INVERSE = 1;
constexpr usint FLIP = 2;

struct mlAnimationInstance {// colocar interval e stepcell

	sint  direction, rangeOfCells, interval, step, flip;

	mlAnimationInstance(usint rangeOfCells, usint direction=0, usint cellInterval = 0, usint stepCell = 0) {
		debugLog("created obj <mlAnimationInstance>");
		this->direction = direction;
		this->rangeOfCells = rangeOfCells-1;
		this->interval = cellInterval + 1;
		this->step = stepCell + 1;
		this->flip = -(stepCell + 1);

		debugLog("interval: ", interval);
		debugLog("direction: ", direction);
		debugLog("rangeOfCells: ", rangeOfCells);
		debugLog("flip: ", flip);
		debugLog("step: ", step);
	}

};

// argumentos: <rangeOfCells, startCell, direction, cellInterval, stepCell>
struct mlAnimation {

	sint start, end, jump, index;

	mlAnimationInstance *stance = nullptr;

	mlAnimation(mlAnimationInstance *stance, usint startCell=0) {
		debugLog("created obj <mlAnimation>");

		this->stance = stance;

		(stance->direction == 2) ? this->index = startCell+1 : this->index = startCell-1;

		this->start = startCell;
		this->end = startCell + stance->rangeOfCells;
		this->jump = 0;
		
		

		debugLog("index: ", index);
		debugLog("start: ", start);
		debugLog("end: ", end);
		debugLog("jump: ", jump);
	}

	~mlAnimation() {
		debugLog("destructing obj <mlAnimation>");
	}

};
/*
void modStart(mlAnimation *self,usint start) {
	(self->stance->direction == 2) ? self->index = start + 1 : self->index = start - 1;
	self->start = start;
}

void modRange(mlAnimation *self, usint range) {
	self->stance->rangeOfCells = range;
	self->end = self->start + range;
}

//ESSA BAGASA NAO FUNCIONA
void modDirection(mlAnimation *self, usint direction) {
	self->direction = direction;
}

void modStep(mlAnimation *self, usint step) {
	self->stance->step = step+1;
}

void modInterval(mlAnimation *self, usint interval) {
	self->stance->interval = interval;
}
*/
usint animNormal(mlAnimation *self) {
	self->index += self->stance->step;
	if (self->index > self->end) self->index = self->start;
	return self->index;
}

usint animInverse(mlAnimation *self) {
	self->index -= self->stance->step;
	if (self->index < self->start) self->index = self->end;
	return self->index;
}

usint animFlip(mlAnimation *self) {
	if (self->index <= self->start || self->index >= self->end) self->stance->flip *= -1;
	self->index += self->stance->flip;
	return self->index;
}

int mlAnim(mlAnimation *self) {
	if (self->jump > 1) {
		self->jump--;
		return self->index;
	}

	self->jump = self->stance->interval;

	if (self->stance->direction == ANIMATION_FORWARD) return animNormal(self);
	if (self->stance->direction == ANIMATION_BACK) return animInverse(self);
	if (self->stance->direction == ANIMATION_FLIP) return animFlip(self);
	return 0;
}



#endif
