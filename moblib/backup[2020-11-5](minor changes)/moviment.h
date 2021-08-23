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
#ifndef MOVIMENT_H
#define MOVIMENT_H

//uso esclusivo para a hipotenusa
#include <cmath>
#include "sheet.h"
 
typedef short int sint;

namespace MOVIMENT {

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
		INSTANCE(float _x=0, float _y=0) {
			x = _x, y = _y;
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

	// classe para movimentacao com teclado flags: NEW_INSTANCE | NEW_INSTANCE_GHOST
	template <class T>
	class KEYBOARD{
	public:
		static const double dirX[8];
		static const double dirY[8];
		sint dirMiddle = 2;
		float vel = 0;
		bool UP = false, DOWN = false, LEFT = false, RIGHT = false;
		T* pos = nullptr;
		
		KEYBOARD(T* pos, float vel = 0) { this->pos = pos, this->vel = vel; }
		~KEYBOARD() {if(pos) delete pos; }
	};

	const double KEYBOARD<INSTANCE_GHOST>::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const double KEYBOARD<INSTANCE_GHOST>::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };
	const double KEYBOARD<INSTANCE>::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const double KEYBOARD<INSTANCE>::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };

	// argumentos: <X, Y>
	template <class T>
	class AUTO{
	public:
		float fX = 0, fY = 0, fH = 0,
			dX = 0, dY = 0, dH = 0,
			vuX = 0, vuY = 0, vel = 0;
		bool stop = true;
		sint dirMiddle = 0, dirExact = 0;
		T* pos = nullptr;

		AUTO(T* pos){ this->pos = pos, this->vel = vel; }
		~AUTO() { if (pos) delete pos; }
	};

	template <class T>
	class MOUSE {
	public:
		T* pos = nullptr;
		bool LEFT = false, RIGTH = false, CENTER = false, MOVING = false;

		MOUSE(T* pos) { this->pos = pos;  }
		~MOUSE() { if (pos) delete pos; }
	};

	template <class T>
	class TOUCH {
	public:
		T* pos = nullptr;
		bool ACTIVE[5] = { false }, MOVING = false;

		TOUCH(T* pos) { this->pos = pos; }
		~TOUCH() { if (pos) delete pos; }
	};

	float getTraceX(INSTANCE_GHOST *self, sint index) { if (index < self->traceSize) return self->traceX[index];  return -100; }
	float getTraceY(INSTANCE_GHOST *self, sint index) { if (index < self->traceSize) return self->traceY[index];  return -100; }

	void setTrace(INSTANCE_GHOST *self, float x, float y) {
		if (self->traceSize <= 0) return;
		for (sint i = self->traceSize - 1, i2 = self->traceSize - 2;i > 0;i--, i2--) { self->traceX[i] = self->traceX[i2], self->traceY[i] = self->traceY[i2]; }
		self->traceX[0] = x, self->traceY[0] = y;
	}

	void setAutoXY(INSTANCE_GHOST *self, float x, float y) {
		self->x = x, self->y = y;
		if (self->traceDelayCount > 1) { self->traceDelayCount--; return; }
		self->traceDelayCount = self->traceDelay;
		setTrace(self, x, y);
	}

	void setAutoTrace(INSTANCE_GHOST *self) {
		if (self->traceDelayCount > 1) { self->traceDelayCount--; return; }
		self->traceDelayCount = self->traceDelay;
		setTrace(self, self->x, self->y);
	}

	// metodo para movimentar
	template <class T>
	void run(KEYBOARD<T> *self, bool all = true) {
			
		if (self->UP && self->LEFT && all) {
			self->pos->x += self->dirX[UP_LEFT] * self->vel,
				self->pos->y += self->dirY[UP_LEFT] * self->vel;
			self->dirMiddle = UP_LEFT;
		}
		else if (self->UP && self->RIGHT && all) {
			self->pos->x += self->dirX[UP_RIGHT] * self->vel,
				self->pos->y += self->dirY[UP_RIGHT] * self->vel;
			self->dirMiddle = UP_RIGHT;
		}
		else if (self->DOWN && self->LEFT && all) {
			self->pos->x += self->dirX[DOWN_LEFT] * self->vel,
				self->pos->y += self->dirY[DOWN_LEFT] * self->vel;
			self->dirMiddle = DOWN_LEFT;
		}
		else if (self->DOWN && self->RIGHT && all) {
			self->pos->x += self->dirX[DOWN_RIGHT] * self->vel,
				self->pos->y += self->dirY[DOWN_RIGHT] * self->vel;
			self->dirMiddle = DOWN_RIGHT;
		}
		else if (self->DOWN) {
			self->pos->x += self->dirX[DOWN] * self->vel,
				self->pos->y += self->dirY[DOWN] * self->vel;
			self->dirMiddle = DOWN;
		}
		else if (self->RIGHT) {
			self->pos->x += self->dirX[RIGHT] * self->vel,
				self->pos->y += self->dirY[RIGHT] * self->vel;
			self->dirMiddle = RIGHT;
		}
		else if (self->UP) {

			self->pos->x += self->dirX[UP] * self->vel,
				self->pos->y += self->dirY[UP] * self->vel;
			self->dirMiddle = UP;
		}
		else if (self->LEFT) {
			self->pos->x += self->dirX[LEFT] * self->vel,
				self->pos->y += self->dirY[LEFT] * self->vel;
			self->dirMiddle = LEFT;
		}

	}

	// metodo para modificar a velocidade
	template <class T>
	void velocity(AUTO<T> *self, float vel) {
		if (self->dX && vel != self->vel) {
			self->vel = vel;
			self->vuX = self->vel / self->dH*self->dX;
			self->vuY = self->vel / self->dH*self->dY; //divisao por 0
		}
	}
	// metodo para modificar a direcao de movimeto
	template <class T>
	void direction(AUTO<T> *self, float x, float y, float vel) {

		if (x == self->pos->x && y == self->pos->y) return;

		self->vel = vel;
		self->stop = false;

		self->dX = x - self->pos->x, self->dY = y - self->pos->y;
		self->fX = x, self->fY = y;

		self->fH = hypot(x, y);
		self->dH = hypot(self->dX, self->dY);

		self->vuX = self->vel / self->dH*self->dX + 0.000001;
		self->vuY = self->vel / self->dH*self->dY + 0.000001;
		x = self->dX, y = self->dY;

		sint tmpDir = 0;

		if (y > x > 0) tmpDir = DOWN;
		if (x > y > 0) tmpDir = RIGHT;
		if (y < x < 0) tmpDir = UP;
		if (x < y < 0) tmpDir = LEFT;
		if (0 < -x < y) tmpDir = DOWN;
		if (0 < -y < x) tmpDir = RIGHT;
		if (0 > -x > y) tmpDir = UP;
		if (0 > -y > x) tmpDir = LEFT;
		if (tmpDir) self->dirExact = tmpDir;

		if (x > 0 && y > 0) tmpDir = DOWN_RIGHT;
		if (x < 0 && y < 0) tmpDir = UP_LEFT;
		if (x < 0 && y > 0) tmpDir = DOWN_LEFT;
		if (x > 0 && y < 0) tmpDir = UP_RIGHT;
		if (tmpDir) self->dirMiddle = tmpDir;
	}

	// metodo para movimentar
	template <class T>
	void run(AUTO<T> *self) {
		short int tmpRun = 1;
		tmpRun *= !(self->vuX > 0 && self->pos->x >= self->fX);
		tmpRun *= !(self->vuX < 0 && self->pos->x <= self->fX);
		tmpRun *= !(self->vuY > 0 && self->pos->y >= self->fY);
		tmpRun *= !(self->vuY < 0 && self->pos->y <= self->fY);
		self->pos->x += self->vuX * tmpRun, self->pos->y += self->vuY *tmpRun;
		self->stop = !tmpRun;
	}
	
}
#endif