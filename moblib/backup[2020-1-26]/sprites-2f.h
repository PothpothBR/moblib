/*


						----------------------------------------------------
						|               Programa feito por                 |
						|     [Bruno Dalagnol] [2018] [versao: sei la]     |
						----------------------------------------------------
						|                                                  |
						|			  /\         /\       ___              |
						|			 /--\_______/--\     /  _|             |
						|			 |  Y       Y  |    / /                |
						|			 |    ==T==    |   / /                 |
						|			 \_____________/  / /                  |
						|				|  _____   \ / /                   |
						|				|           \ /                    |
						|				|  |--|  |\  |                     |
						|				|__||_|__||__|                     |
						----------------------------------------------------



	||||||    ||||||    ||||||			||||||    ||||||   |     |  ||     |    ||||||			||||||
	|    |   |      |   |     |			|     |   |     |  |     |  | |    |   |      |			|     |
	|    |  |        |  |     |			|     |   |     |  |     |  |  |   |  |        |		|      |
	|||||   |        |  | |||||			||||||    | |||||  |     |  |   |  |  |        |		|      |
	|       |        |  |  |			|     |   |  |     |     |  |    | |  |        |		|      |
	|        |      |   |   |			|     |   |   |    |	 |  |     ||   |      |			|     |
	|         ||||||    |    |			|||||||   |    |   |||||||  |      |    ||||||			||||||   |||

	*/
#ifndef SPRITES2F_H
#define SPRITES2F_H

#include "debug_log.h"


typedef unsigned short int usint;

constexpr usint NORMAL = 0;
constexpr usint INVERSE = 1;
constexpr usint FLIP = 2;

struct SpriteAnimation {

	usint start,end,
		  interval,jump,direction,rangeOfCells,flip,step,count;

	explicit SpriteAnimation( usint rangeOfCells, usint startCell=1, usint direction=0, usint cellInterval=0, usint stepCell=0) {
		debugLog("created obj <Sprite_secondFloor>");

		(direction == 2) ? this->count = startCell : this->count = startCell-2;

		this->start = startCell - 1;
		this->end = startCell + rangeOfCells - 2;
		this->interval = cellInterval + 1;
		this->jump = 0;
		this->direction = direction;
		this->rangeOfCells = rangeOfCells - 1;
		this->flip = -(stepCell + 1);
		this->step = stepCell + 1;

		debugLog("start: ", start);
		debugLog("end: ", end);
		debugLog("interval: ", interval);
		debugLog("jump: ", jump);
		debugLog("direction: ", direction);
		debugLog("rangeOfCells: ", rangeOfCells);
		debugLog("flip: ", flip);
		debugLog("step: ", step);


	}

};

void modStart(SpriteAnimation *self,usint start) {
	start--;
	(self->direction == 2)? self->count = start : self->count = start-2;
	self->end = start - 1 + self->rangeOfCells;
}

void modRange(SpriteAnimation *self, usint range) {
	self->rangeOfCells = range - 1;
	self->end = self->start + range - 1;
}

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
	self->count += self->step;
	if (self->count > self->end) self->count = self->start;
	return self->count;
}

usint animInverse(SpriteAnimation *self) {
	self->count -= self->step;
	if (self->count < self->start) self->count = self->end;
	return self->count;
}

usint animFlip(SpriteAnimation *self) {
	if (self->count <= self->start || self->count >= self->end) self->flip *= -1;
	self->count += self->flip*self->step; //nao testado pode dar erro
	return self->count;
}

usint anim(SpriteAnimation *self) {
	if (self->jump > 1) {
		self->jump--;
	}
	else {
		self->jump = self->interval;

		switch(self->direction) {
		case 0:
			return animNormal(self);
			break;
		case 1:
			return animInverse(self);
			break;
		case 2:
			return animFlip(self);
			break;
		}
	}
}



#endif
