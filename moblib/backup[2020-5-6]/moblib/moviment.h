/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |		   	    /\         /\       ___              |
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
#ifndef MOVIMENT_H
#define MOVIMENT_H

//uso esclusivo para a hipotenusa
#include <cmath>

#include "debug_log.h"
#include "sheet.h"
 
typedef  short int sint;



namespace MOB_MOVIMENT {

	constexpr sint UP = 0;
	constexpr sint LEFT = 1;
	constexpr sint DOWN = 2;
	constexpr sint RIGHT = 3;

	constexpr sint UP_LEFT = 4;
	constexpr sint UP_RIGHT = 5;
	constexpr sint DOWN_LEFT = 6;
	constexpr sint DOWN_RIGHT = 7;

	// classe simples somente com atributos basicos
	class INSTANCE {
	public:
		float x = 0, y = 0;
		INSTANCE(float _x, float _y) {
			x = _x;
			y = _y;
		}
	};
	
	class INSTANCE_GHOST : public INSTANCE {
	public:
		float *traceX, *traceY;
		sint traceSize, traceDelay, traceDelayCount;

		INSTANCE_GHOST(float x, float y, sint traceSize = 0, sint traceDelay = 0) : INSTANCE(x, y) {
			if (traceSize) {
				this->traceX = (float *)calloc(traceSize, sizeof(float));
				this->traceY = (float *)calloc(traceSize, sizeof(float));
				for (int i = 0; i < traceSize;i++) { traceX[i] = x, traceY[i] = y; }
			}
			else { this->traceX = nullptr, this->traceY = nullptr; }
			this->traceSize = traceSize, this->traceDelay = traceDelay, this->traceDelayCount = traceDelay;
		}
	private:
		~INSTANCE_GHOST() {
			if (traceX) free(traceX); if (traceY) free(traceY);
		}
	};

	// argumentos: <AUTO *, mlSheet *>
	class FORM {
	public:

		float *x, *y, width, height;

		FORM(MOB_MOVIMENT::INSTANCE* selfMoviment, mlSheet *selfSheet) {
			this->x = &selfMoviment->x;
			this->y = &selfMoviment->y;

			this->width = selfSheet->cellWidth;
			this->height = selfSheet->cellHeight;
		}

		FORM(MOB_MOVIMENT::INSTANCE* selfMoviment, float width, float height) {

			this->x = &selfMoviment->x;
			this->y = &selfMoviment->y;
			this->width = width;
			this->height = height;

		}

	};

	// classe para movimentacao com teclado flags: NEW_INSTANCE | NEW_INSTANCE_GHOST
	template <class T>
	class KEYBOARD{
	public:
		static const float dirX[8];
		static const float dirY[8];
		sint dirMiddle = 2;
		float vel = 0;
		bool UP = false, DOWN = false, LEFT = false, RIGHT = false;
		T* instance = nullptr;
		
		KEYBOARD(T* instance, float vel = 0) { this->instance = instance, this->vel = vel; }
		~KEYBOARD() {if(instance) delete instance; }
	};

	const float KEYBOARD<INSTANCE_GHOST>::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const float KEYBOARD<INSTANCE_GHOST>::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };
	const float KEYBOARD<INSTANCE>::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const float KEYBOARD<INSTANCE>::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };

	// argumentos: <X, Y>
	template <class T>
	class AUTO{
	public:
		float fX = 0, fY = 0, fH = 0,
			dX = 0, dY = 0, dH = 0,
			vuX = 0, vuY = 0, vel = 0;
		bool stop = true;
		sint dirMiddle = 0, dirExact = 0;
		T* instance = nullptr;

		AUTO(T* instance){ this->instance = instance, this->vel = vel; }
		~AUTO() { if (instance) delete instance; }
	};

	template <class T>
	class MOUSE {
		T* instance = nullptr;
		bool LEFT = false, RIGTH = false, CENTER = false, MOVING = false;

		MOUSE(T* instance) { this->instance = instance;  }
		~MOUSE() { if (instance) delete instance; }
	};

	template <class T>
	class TOUCH {
		T* instance = nullptr;
		bool ACTIVE[5] = { false }, MOVING = false;

		TOUCH(T* instance) { this->instance = instance; }
		~TOUCH() { if (instance) delete instance; }
	};
}

#define INSTANCE(x, y) (MOB_MOVIMENT::INSTANCE*) new MOB_MOVIMENT::INSTANCE(x, y)
#define INSTANCE_GHOST(x, y, traceSize, traceDelay) (MOB_MOVIMENT::INSTANCE_GHOST*) new MOB_MOVIMENT::INSTANCE_GHOST(x, y, traceSize, traceDelay)

#endif