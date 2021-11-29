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
	mlMovimentAuto *movA = nullptr;
	mlMovimentKeys *movK = nullptr;
	mlMovimentInstance *movI = nullptr;
	mlMapping *map = nullptr;

	mlAnimation* getAnim(sint index) { if (index < animSize) return anim[index]; return anim[0]; }

	sint animSize = 0;
	sint freeAnimSize = 0;

	mlObject(){
		debugLog("created obj <mlObject>");
	}

	void initSheet(sint width, sint height, sint cols, sint rows) { sheet = new mlSheet(width, height, cols, rows); }

	void initMovimentInstance(float x, float y, sint traceSize = 0, sint traceDelay = 0) {
		if (movK) delete movK;
		else if (movA) delete movA;
		movI = new mlMovimentInstance(x, y, traceSize, traceDelay);
	}
	void initMoviment(float x, float y, sint traceSize = 0, sint traceDelay = 0) {
		if (movI) delete movI;
		else if (movK) delete movK;
		movA = new mlMovimentAuto(x,y, traceSize, traceDelay);
	}
	void initMovimentKeys(float x, float y,float vel, sint traceSize = 0, sint traceDelay = 0) {
		if (movI) delete movI;
		if (movA) delete movA;
		movK = new mlMovimentKeys(x,y,vel, traceSize, traceDelay);
	}
	void initAnimationInstance(sint rangeOfCells, sint direction = 0, sint cellInterval = 0, sint stepCell = 0) {
		animI = new mlAnimationInstance(rangeOfCells, direction , cellInterval , stepCell);
	}
	void initFormat(float width, float height) {
		if (movA) form = new mlFormat(movA, width, height);
		else if (movK) form = new mlFormat(movK, width, height);
		else if (movI) form = new mlFormat(movI, sheet->width(), sheet->height());
	}
	void initFormat() {
		if (sheet) {
			if (movA) form = new mlFormat(movA, sheet->width(), sheet->height());
			else if (movK) form = new mlFormat(movK, sheet->width(), sheet->height());
			else if (movI) form = new mlFormat(movI, sheet->width(), sheet->height());
		}
	}
	void initMapping(const sint width, const sint height) {
		if (sheet) {
			if (movA) map = new mlMapping(sheet, movA, width, height);
			else if (movK) map = new mlMapping(sheet, movK, width, height);
			else if (movI) map = new mlMapping(sheet, movI, width, height);
		}
	}
	void initAnimation(sint animSize=1) {
		this->animSize = animSize;
		freeAnimSize = animSize;
		anim = (mlAnimation**)calloc(animSize, sizeof(mlAnimation *));
	}

	void addAnimation(sint startCell = 0) { if(freeAnimSize > 0) anim[--freeAnimSize] = new mlAnimation(animI,startCell); }

	~mlObject() {
		debugLog("destructing obj <mlObject>");
		for (int i = 0;i < animSize;i++) {
			delete anim[i];
		}
		free(anim);

		delete sheet;
		delete form;
		delete movI;
		delete movA;
		delete map;
		delete movK;
		delete animI;
	}
};

#endif
