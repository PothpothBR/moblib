#ifndef MOBLIB_H
#define MOBLIB_H

#include "sheet.h"
#include "animation.h"
#include "moviment.h"
#include "format.h"
#include "mapping.h"

//argumentos <nenhum>
struct mlObject {
private:
	mlAnimation **anim = nullptr;
public:
	mlSheet *sheet = nullptr;
	mlAnimationInstance *animI = nullptr;
	mlFormat *form = nullptr;
	mlMovimentAuto *mov = nullptr;
	mlMovimentKeys *movK = nullptr;
	mlMovimentInstance *movI = nullptr;
	//mlMapping *map = nullptr;

	mlAnimation* getAnim(usint index) { if (index < animSize) return anim[index]; return anim[0]; }

	usint animSize = 0;
	usint freeAnimSize = 0;

	mlObject(){
		debugLog("created obj <mlObject>");
	}

	void initSheet(usint width, usint height, usint cols, usint rows) { sheet = new mlSheet(width, height, cols, rows); }

	void initMovimentInstance(float x, float y, usint traceSize = 0, usint traceDelay = 0) {
		if (movK) delete movK;
		if (mov) delete mov;
		movI = new mlMovimentInstance(x, y, traceSize, traceDelay);
	}
	void initMoviment(float x, float y, usint traceSize = 0, usint traceDelay = 0) {
		if (movI) delete movI;
		if (movK) delete movK;
		mov = new mlMovimentAuto(x,y, traceSize, traceDelay);
	}
	void initMovimentKeys(float x, float y,float vel, usint traceSize = 0, usint traceDelay = 0) {
		if (movI) delete movI;
		if (mov) delete mov;
		movK = new mlMovimentKeys(x,y,vel, traceSize, traceDelay);
	}
	void initAnimationInstance(usint rangeOfCells, usint direction = 0, usint cellInterval = 0, usint stepCell = 0) {
		animI = new mlAnimationInstance(rangeOfCells, direction , cellInterval , stepCell);
	}
	void initFormat(float width, float height) {
		if (mov) form = new mlFormat(mov, width, height);
		if (movK) form = new mlFormat(movK, width, height);
		if (movI) form = new mlFormat(movI, sheet->getWidth(), sheet->getHeight());
	}
	void initFormat() {
		if (sheet) {
			if (mov) form = new mlFormat(mov, sheet->getWidth(), sheet->getHeight());
			if (movK) form = new mlFormat(movK, sheet->getWidth(), sheet->getHeight());
			if (movI) form = new mlFormat(movI, sheet->getWidth(), sheet->getHeight());
		}
	}
	//void initMapping(const usint width,const usint height,usint init[]) { map = new mlMapping(width, height,init); }
	void initAnimation(usint animSize=1) {
		this->animSize = animSize;
		freeAnimSize = animSize;
		anim = (mlAnimation**)calloc(animSize, sizeof(mlAnimation *));
	}

	void addAnimation(usint startCell = 0) { if(freeAnimSize > 0) anim[--freeAnimSize] = new mlAnimation(animI,startCell); }

	~mlObject() {
		debugLog("destructing obj <mlObject>");
		for (int i = 0;i < animSize;i++) {
			delete anim[i];
		}
		free(anim);

		delete sheet;
		delete form;
		delete movI;
		delete mov;
		//delete map;
		delete movK;
		delete animI;
	}
};

#endif
