#ifndef MOBLIB_H
#define MOBLIB_H

#include "sheet.h"
#include "animation.h"
#include "moviment.h"
#include "format.h"
#include "mapping.h"

//argumentos <nenhum>
template <class mlMoviment=mlMovimentInstance>
struct mlObject {
private:
	mlAnimation **anim = nullptr;
public:
	mlSheet *sheet = nullptr;
	mlAnimationInstance *animI = nullptr;
	mlFormat *form = nullptr;
	mlMoviment *mov = nullptr;
	mlMapping *mappg = nullptr;

	mlAnimation* getAnim(sint index) { if (index < animSize) return anim[index]; return anim[0]; }

	sint animSize = 0, freeAnimSize = 0;

	mlObject(){ debugLog("created obj <mlObject>"); }

	void initSheet(sint width, sint height, sint cols, sint rows) { sheet = new mlSheet(width, height, cols, rows); }

	void initMoviment(float x, float y, sint traceSize = 0, sint traceDelay = 0) { mov = new mlMoviment(x,y, traceSize, traceDelay); }

	void initAnimationInstance(sint rangeOfCells, sint direction = 0, sint cellInterval = 0, sint stepCell = 0) { animI = new mlAnimationInstance(rangeOfCells, direction , cellInterval , stepCell); }
	
	void initFormat(float width, float height) { form = new mlFormat(mov, width, height); }
	
	void setAnimation(sint startCell = 0) { if(freeAnimSize > 0) anim[--freeAnimSize] = new mlAnimation(animI,startCell); }

	void initFormat() {
		if (sheet) {
			form = new mlFormat(mov, sheet->width(), sheet->height());
		}
	}
	void initMapping(sint w, sint h, sint lx, sint ly, sint lw, sint lh) {
		if (sheet) {
			mappg = new mlMapping(sheet, mov, w, h, lx, ly, lw, lh);
		}
	}
	void initAnimation(sint animSize=1) {
		this->animSize = animSize;
		freeAnimSize = animSize;
		anim = (mlAnimation**)calloc(animSize, sizeof(mlAnimation *));
	}
	
	~mlObject() {
		debugLog("destructing obj <mlObject>");
		for (int i = 0;i < animSize;i++) {
			delete anim[i];
		}
		free(anim);

		delete sheet;
		delete form;
		delete mov;
		delete mappg;
		delete animI;
	}
};

#endif
