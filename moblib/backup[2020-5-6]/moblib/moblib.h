#ifndef MOBLIB_H
#define MOBLIB_H

#include "sheet.h"
#include "animation.h"
#include "moviment.h"
#include "mapping.h"

//argumentos <nenhum>
template <class T>
class mlObject {
public:
	mlAnimation **animation = nullptr;
	mlSheet *sheet = nullptr;
	mlAnimationInstance *animInstance = nullptr;
	mlFormat *format = nullptr;
	T *moviment = nullptr;
	mlMapping *mapping = nullptr;
	sint animSize = 0;

	mlObject(sint animation_buffer_size) { animSize = animation_buffer_size; debugLog("created obj <mlObject>"); }
	
	mlObject(){ debugLog("created obj <mlObject>"); }

	~mlObject() {
		debugLog("destructing obj <mlObject>");
		for (int i = 0;i < animSize;i++) {
			delete animation[i];
		}
		free(animation);

		delete sheet;
		delete format;
		delete moviment;
		delete mapping;
		delete animInstance;
	}
};

mlSheet* initSheet(sint width, sint height, sint cols, sint rows) { 
	return new mlSheet(width, height, cols, rows); }

mlAnimationInstance* initAnimationInstance(sint rangeOfCells, sint direction = 0, sint cellInterval = 0, sint stepCell = 0) { 
	return new mlAnimationInstance(rangeOfCells, direction, cellInterval, stepCell); }

mlAnimation** initAnimation(sint *buffer_size) {
	return (mlAnimation**)calloc(*buffer_size, sizeof(mlAnimation *));}

mlAnimation* setAnimation(mlAnimationInstance *self, sint startCell = 0) {
	return new mlAnimation(self, startCell); }

template <class mlMoviment = mlMovimentInstanceWithGhost>
mlMoviment* initMoviment(float x, float y, float vel=0, sint traceSize = 0, sint traceDelay = 0) {
	return new mlMoviment(x, y, vel, traceSize, traceDelay); }

template <class mlMoviment = mlMovimentInstanceWithGhost>
mlFormat* initFormat(mlMoviment *moviment,float width, float height) {
	return new mlFormat(moviment, width, height); }

template <class mlMoviment = mlMovimentInstanceWithGhost>
mlFormat* initFormat(mlMoviment *moviment, mlSheet *sheet) {
	return new mlFormat(moviment, sheet); }

template <class mlMoviment = mlMovimentInstanceWithGhost>
mlMapping* initMapping(sint w, sint h, sint lx, sint ly, sint lw, sint lh) {
	return new mlMapping(w, h, lx, ly, lw, lh); }

#endif
