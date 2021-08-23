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

#include "debug_log.h"
#include "sheet.h"
 
typedef  short int sint;

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
		INSTANCE(float _x, float _y) {
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

	// argumentos: <AUTO *, mlSheet *>
	class FORM {
	public:

		float *x, *y, width, height;

		FORM(INSTANCE* selfMoviment, SHEET *selfSheet) {
			this->x = &selfMoviment->x;
			this->y = &selfMoviment->y;

			this->width = selfSheet->cellWidth;
			this->height = selfSheet->cellHeight;
		}

		FORM(INSTANCE* selfMoviment, float width, float height) {

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
		T* pos = nullptr;
		
		KEYBOARD(T* pos, float vel = 0) { this->pos = pos, this->vel = vel; }
		~KEYBOARD() {if(pos) delete pos; }
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
		T* pos = nullptr;

		AUTO(T* pos){ this->pos = pos, this->vel = vel; }
		~AUTO() { if (pos) delete pos; }
	};

	template <class T>
	class MOUSE {
		T* pos = nullptr;
		bool LEFT = false, RIGTH = false, CENTER = false, MOVING = false;

		MOUSE(T* pos) { this->pos = pos;  }
		~MOUSE() { if (pos) delete pos; }
	};

	template <class T>
	class TOUCH {
		T* pos = nullptr;
		bool ACTIVE[5] = { false }, MOVING = false;

		TOUCH(T* pos) { this->pos = pos; }
		~TOUCH() { if (pos) delete pos; }
	};

	namespace MTH {
		using namespace MOVIMENT;

		bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
			return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
		}

		bool collision(FORM *self1, FORM *self2) {
			return(*self1->x < *self2->x + self2->width && *self1->x + self1->width > *self2->x &&* self1->y < *self2->y + self2->height && *self1->y + self1->height > *self2->y);
		}

		bool collision(FORM *self1, int x2, int y2, int w2, int h2) {
			return(*self1->x < x2 + w2 && *self1->x + self1->width > x2 && *self1->y < y2 + h2 && *self1->y + self1->height > y2);
		}

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

			if (self->activeUP && self->activeLEFT && all) {
				self->x += self->dirX[UP_LEFT] * self->vel,
					self->y += self->dirY[UP_LEFT] * self->vel;
				self->dirMiddle = UP_LEFT;
			}
			else if (self->activeUP && self->activeRIGHT && all) {
				self->x += self->dirX[UP_RIGHT] * self->vel,
					self->y += self->dirY[UP_RIGHT] * self->vel;
				self->dirMiddle = UP_RIGHT;
			}
			else if (self->activeDOWN && self->activeLEFT && all) {
				self->x += self->dirX[DOWN_LEFT] * self->vel,
					self->y += self->dirY[DOWN_LEFT] * self->vel;
				self->dirMiddle = DOWN_LEFT;
			}
			else if (self->activeDOWN && self->activeRIGHT && all) {
				self->x += self->dirX[DOWN_RIGHT] * self->vel,
					self->y += self->dirY[DOWN_RIGHT] * self->vel;
				self->dirMiddle = DOWN_RIGHT;
			}
			else if (self->activeDOWN) {
				self->x += self->dirX[DOWN] * self->vel,
					self->y += self->dirY[DOWN] * self->vel;
				self->dirMiddle = DOWN;
			}
			else if (self->activeRIGHT) {
				self->x += self->dirX[RIGHT] * self->vel,
					self->y += self->dirY[RIGHT] * self->vel;
				self->dirMiddle = RIGHT;
			}
			else if (self->activeUP) {

				self->x += self->dirX[UP] * self->vel,
					self->y += self->dirY[UP] * self->vel;
				self->dirMiddle = UP;
			}
			else if (self->activeLEFT) {
				self->x += self->dirX[LEFT] * self->vel,
					self->y += self->dirY[LEFT] * self->vel;
				self->dirMiddle = LEFT;
			}

		}
		template <class T>
		void run(KEYBOARD<T> *self, FORM *selfcolid, FORM *colid, bool all = true) {

			if (self->activeUP && self->activeLEFT && all) {
				float tempx = self->dirX[UP_LEFT] * self->vel;
				float tempy = self->dirY[UP_LEFT] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = UP_LEFT;
			}
			else if (self->activeUP && self->activeRIGHT && all) {
				float tempx = self->dirX[UP_RIGHT] * self->vel;
				float tempy = self->dirY[UP_RIGHT] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = UP_RIGHT;
			}
			else if (self->activeDOWN && self->activeLEFT && all) {
				float tempx = self->dirX[DOWN_LEFT] * self->vel;
				float tempy = self->dirY[DOWN_LEFT] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = DOWN_LEFT;
			}
			else if (self->activeDOWN && self->activeRIGHT && all) {
				float tempx = self->dirX[DOWN_RIGHT] * self->vel;
				float tempy = self->dirY[DOWN_RIGHT] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = DOWN_RIGHT;
			}
			else if (self->activeDOWN) {

				float tempx = self->dirX[DOWN] * self->vel;
				float tempy = self->dirY[DOWN] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = DOWN;
			}
			else if (self->activeRIGHT) {
				float tempx = self->dirX[RIGHT] * self->vel;
				float tempy = self->dirY[RIGHT] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = RIGHT;
			}
			else if (self->activeUP) {

				float tempx = self->dirX[UP] * self->vel;
				float tempy = self->dirY[UP] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
				self->dirMiddle = UP;
			}
			else if (self->activeLEFT) {
				float tempx = self->dirX[LEFT] * self->vel;
				float tempy = self->dirY[LEFT] * self->vel;

				if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

				self->x += tempx,
				self->y += tempy;
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

			if (x == self->x && y == self->y) return;

			self->vel = vel;
			self->stop = false;

			self->dX = x - self->x, self->dY = y - self->y;
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
			tmpRun *= !(self->vuX > 0 && self->x >= self->fX);
			tmpRun *= !(self->vuX < 0 && self->x <= self->fX);
			tmpRun *= !(self->vuY > 0 && self->y >= self->fY);
			tmpRun *= !(self->vuY < 0 && self->y <= self->fY);
			self->x += self->vuX * tmpRun, self->y += self->vuY *tmpRun;
			self->stop = !tmpRun;
		}
	}

}


#endif