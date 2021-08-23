#ifndef MOBLIB_H
#define MOBLIB_H

#include "cores.h"
#include "sheet.h"
#include "animation.h"
#include "moviment.h"
#include "format.h"
#include "mapping.h"

struct mlObject {
private:
	mlAnimation **anim = nullptr;
public:
	mlSheet *sheet = nullptr;
	mlAnimationInstance *animI = nullptr;
	mlFormat *form = nullptr;
	mlMoviment *mov = nullptr;
	mlMovimentKeys *movK = nullptr;

	mlAnimation* getAnimation(usint index) { if (index < animSize) return anim[index]; return anim[0]; }

	usint animSize = 0;
	usint freeAnimSize = 0;

	mlObject(){
	}
	void initSheet(usint width, usint height, usint cols, usint rows) {
		sheet = new mlSheet(width, height, cols, rows);
	}
	void initMoviment(float x, float y, usint traceSize = 0, usint traceDelay = 0) {
		if (movK) delete movK;
		mov = new mlMoviment(x,y);
	}
	void initMovimentKeys(float x, float y, usint traceSize = 0, usint traceDelay = 0) {
		if (mov) delete mov;
		movK = new mlMovimentKeys(x,y);
	}
	void initAnimationInstance(usint rangeOfCells, usint direction = 0, usint cellInterval = 0, usint stepCell = 0) {
		animI = new mlAnimationInstance(rangeOfCells, direction , cellInterval , stepCell);
	}
	void initFormat(float width, float height) {
		if (mov) form = new mlFormat(mov, width, height);
		if (movK) form = new mlFormat(movK, width, height);
	}

	void initAnimation(usint animSize=1) {
		this->animSize = animSize;
		freeAnimSize = animSize;
		anim = (mlAnimation**)calloc(animSize, sizeof(mlAnimation *));
	}

	void addAnimation(usint startCell = 0) {
		if(freeAnimSize > 0) anim[--freeAnimSize] = new mlAnimation(animI,startCell);
	}

	~mlObject() {

		for (int i = 0;i < animSize;i++) {
			delete anim[i];
		}
		free(anim);

		delete sheet;
		delete form;
		delete mov;
		delete movK;
		delete animI;

	}
};

#endif
