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

// argumentos: <rangeOfCells, startCell, direction, cellInterval, stepCell>
struct SpriteAnimation {

	usint start, end,
		interval, jump, direction, rangeOfCells,
		flip, step, index;

	SpriteAnimation( usint rangeOfCells, usint startCell=0, usint direction=0, usint cellInterval=0, usint stepCell=0) {
		debugLog("created obj <SpriteAnimation>");

		(direction == 2) ? this->index = startCell+1 : this->index = startCell-1;

		this->start = startCell;
		this->end = startCell + rangeOfCells - 1;
		this->interval = cellInterval + 1;
		this->jump = 0;
		this->direction = direction;
		this->rangeOfCells = rangeOfCells - 1;
		this->flip = -(stepCell + 1);
		this->step = stepCell + 1;

		debugLog("index: ", this->index);
		debugLog("start: ", start);
		debugLog("end: ", end);
		debugLog("interval: ", interval);
		debugLog("jump: ", jump);
		debugLog("direction: ", direction);
		debugLog("rangeOfCells: ", rangeOfCells);
		debugLog("flip: ", flip);
		debugLog("step: ", step);


	}

	~SpriteAnimation() {
		debugLog("destructing obj <SpriteAnimation>");
	}

};

void modStart(SpriteAnimation *self,usint start) {
	start--;
	(self->direction == ANIMATION_FLIP)? self->index = start : self->index = start-2;
	self->end = start - 1 + self->rangeOfCells;
}

void modRange(SpriteAnimation *self, usint range) {
	self->rangeOfCells = range - 1;
	self->end = self->start + range - 1;
}
//ESSA BAGASA NAO FUNCIONA
void modDirection(SpriteAnimation *self, usint direction) {
	self->direction = direction;
}

void modStep(SpriteAnimation *self, usint step) {
	self->step = step+1;
}

void modInterval(SpriteAnimation *self, usint interval) {
	self->interval = interval;
}

usint animNormal(SpriteAnimation *self) {
	self->index += self->step;
	if (self->index > self->end) self->index = self->start;
	return self->index;
}

usint animInverse(SpriteAnimation *self) {
	self->index -= self->step;
	if (self->index < self->start) self->index = self->end;
	return self->index;
}

usint animFlip(SpriteAnimation *self) {
	if (self->index <= self->start || self->index >= self->end) self->flip *= -1;
	self->index += self->flip;
	return self->index;
}

int anim(SpriteAnimation *self) {
	if (self->jump > 1) {
		self->jump--;
		return self->index;
	}

	self->jump = self->interval;

	if (self->direction == ANIMATION_FORWARD) return animNormal(self);
	if (self->direction == ANIMATION_BACK) return animInverse(self);
	if (self->direction == ANIMATION_FLIP) return animFlip(self);
		
}



#endif
