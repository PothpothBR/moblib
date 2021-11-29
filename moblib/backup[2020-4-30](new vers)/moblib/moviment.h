/*----------------------------------------------------
  |               Programa feito por                 |
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
  ----------------------------------------------------*/
#ifndef MOVIMENT_H
#define MOVIMENT_H

//uso esclusivo para a hipotenusa
#include <cmath>

#include "debug_log.h"
 
typedef  short int sint;

constexpr sint mlUP = 0;
constexpr sint mlLEFT = 1;
constexpr sint mlDOWN = 2;
constexpr sint mlRIGHT = 3;

constexpr sint mlUP_LEFT = 4;
constexpr sint mlUP_RIGHT = 5;
constexpr sint mlDOWN_LEFT = 6;
constexpr sint mlDOWN_RIGHT = 7;

// classe simples somente com atributos basicos e sem inicializador
class mlMovimentInstance{
public:
	float x = 0, y = 0;
};


// argumentos: <mlMovimentAuto *, mlSheet *>
class mlFormat {
public:

	float *x, *y, width, height;

	mlFormat(mlMovimentInstance* selfMoviment, mlSheet *selfSheet) {
		this->x = &selfMoviment->x;
		this->y = &selfMoviment->y;

		this->width = selfSheet->cellWidth;
		this->height = selfSheet->cellHeight;
	}

	mlFormat(mlMovimentInstance* selfMoviment, float width, float height) {

		this->x = &selfMoviment->x;
		this->y = &selfMoviment->y;
		this->width = width;
		this->height = height;

	}

};

bool sampleCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

bool sampleCollision(mlFormat *self1, mlFormat *self2) {
	return(*self1->x < *self2->x + self2->width && *self1->x + self1->width > *self2->x &&* self1->y < *self2->y + self2->height && *self1->y + self1->height > *self2->y);
}

bool sampleCollision(mlFormat *self1, int x2, int y2, int w2, int h2) {
	return(*self1->x < x2 + w2 && *self1->x + self1->width > x2 && *self1->y < y2 + h2 && *self1->y + self1->height > y2);
}

class mlMovimentInstanceWithGhost: public mlMovimentInstance {
public:
	float *traceX, *traceY ;
	sint traceSize, traceDelay, traceDelayCount;
	

	mlMovimentInstanceWithGhost(float x, float y, sint traceSize=0, sint traceDelay=0) {
		this->x = x;
		this->y = y;
		debugLog("created obj <mlMovimentInstance>");
		debugLog("position X:", x, "Y:", y);
		debugLog("size of trace:", traceSize);
		debugLog("trace delay:", traceDelay);
		if (traceSize) {
			this->traceX = (float *)calloc(traceSize, sizeof(float));
			this->traceY = (float *)calloc(traceSize, sizeof(float));
			for (int i = 0; i < traceSize;i++) { traceX[i] = x, traceY[i] = y; }
		}
		else { this->traceX = nullptr, this->traceY = nullptr; }
		this->traceSize = traceSize, this->traceDelay = traceDelay, this->traceDelayCount = traceDelay;
	}
	~mlMovimentInstanceWithGhost(){
		debugLog("destructing obj <mlMovimentInstance>"); 
		if (traceX) free(traceX); if (traceY) free(traceY);
	}
};

void setTrace(mlMovimentInstanceWithGhost *self, float x, float y) {
	if (self->traceSize <= 0) return;
	for (sint i = self->traceSize - 1, i2 = self->traceSize - 2;i > 0;i--, i2--) { self->traceX[i] = self->traceX[i2], self->traceY[i] = self->traceY[i2]; }
	self->traceX[0] = x, self->traceY[0] = y;
}

float getTraceX(mlMovimentInstanceWithGhost *self, sint index) { if (index < self->traceSize) return self->traceX[index];  return -100; }
float getTraceY(mlMovimentInstanceWithGhost *self, sint index) { if (index < self->traceSize) return self->traceY[index];  return -100; }

void setAutoXY(mlMovimentInstanceWithGhost *self, float x, float y) {
	self->x = x, self->y = y;
	if (self->traceDelayCount > 1) { self->traceDelayCount--; return; }
	self->traceDelayCount = self->traceDelay;
	setTrace(self, x, y);
}

void setAutoTrace(mlMovimentInstanceWithGhost *self) {
	if (self->traceDelayCount > 1) { self->traceDelayCount--; return; }
	self->traceDelayCount = self->traceDelay;
	setTrace(self, self->x, self->y);
}


class mlMovimentKeys : public mlMovimentInstanceWithGhost {
public:
	static const float dirX[];
	static const float dirY[];
	sint dirMiddle = 2;
	float vel = 0;
	bool activeUP = false, activeDOWN = false, activeLEFT = false, activeRIGHT = false;

	mlMovimentKeys(float x, float y, float vel = 0,sint traceSize = 0,sint traceDelay = 0): mlMovimentInstanceWithGhost(x, y, traceSize, traceDelay) {
		debugLog("created obj <mlMovimentKeys>");
		debugLog("position X:", x, "Y:", y);
		debugLog("velocity:", vel);
		this->vel=vel;
	}

	~mlMovimentKeys() {
		debugLog("destructing obj <mlMovimentKeys>");
	}
};

const float mlMovimentKeys::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
const float mlMovimentKeys::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };



// metodo para movimentar
void mlRun(mlMovimentKeys *self, bool all=true) {

	if (self->activeUP && self->activeLEFT && all) {
		self->x += self->dirX[mlUP_LEFT] * self->vel,
		self->y += self->dirY[mlUP_LEFT] * self->vel;
		self->dirMiddle = mlUP_LEFT;
	}
	else if (self->activeUP && self->activeRIGHT && all) {
		self->x += self->dirX[mlUP_RIGHT] * self->vel,
		self->y += self->dirY[mlUP_RIGHT] * self->vel;
		self->dirMiddle = mlUP_RIGHT;
	}
	else if (self->activeDOWN && self->activeLEFT && all) {
		self->x += self->dirX[mlDOWN_LEFT] * self->vel,
		self->y += self->dirY[mlDOWN_LEFT] * self->vel;
		self->dirMiddle = mlDOWN_LEFT;
	}
	else if (self->activeDOWN && self->activeRIGHT && all) {
		self->x += self->dirX[mlDOWN_RIGHT] * self->vel,
		self->y += self->dirY[mlDOWN_RIGHT] * self->vel;
		self->dirMiddle = mlDOWN_RIGHT;
	}
	else if (self->activeDOWN) {
		self->x += self->dirX[mlDOWN] * self->vel,
		self->y += self->dirY[mlDOWN] * self->vel;
		self->dirMiddle = mlDOWN;
	}
	else if (self->activeRIGHT) {
		self->x += self->dirX[mlRIGHT] * self->vel,
		self->y += self->dirY[mlRIGHT] * self->vel;
		self->dirMiddle = mlRIGHT;
	}
	else if (self->activeUP) {

		self->x += self->dirX[mlUP] * self->vel,
		self->y += self->dirY[mlUP] * self->vel;
		self->dirMiddle = mlUP;
	}
	else if (self->activeLEFT) {
		self->x += self->dirX[mlLEFT] * self->vel,
		self->y += self->dirY[mlLEFT] * self->vel;
		self->dirMiddle = mlLEFT;
	}

}

void mlRun(mlMovimentKeys *self, mlFormat *selfcolid, mlFormat *colid, bool all = true) {

	if (self->activeUP && self->activeLEFT && all) {
		float tempx = self->dirX[mlUP_LEFT] * self->vel;
		float tempy = self->dirY[mlUP_LEFT] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
		self->y += tempy;
		self->dirMiddle = mlUP_LEFT;
	}
	else if (self->activeUP && self->activeRIGHT && all) {
		float tempx = self->dirX[mlUP_RIGHT] * self->vel;
		float tempy = self->dirY[mlUP_RIGHT] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
			self->y += tempy;
		self->dirMiddle = mlUP_RIGHT;
	}
	else if (self->activeDOWN && self->activeLEFT && all) {
		float tempx = self->dirX[mlDOWN_LEFT] * self->vel;
		float tempy = self->dirY[mlDOWN_LEFT] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
			self->y += tempy;
		self->dirMiddle = mlDOWN_LEFT;
	}
	else if (self->activeDOWN && self->activeRIGHT && all) {
		float tempx = self->dirX[mlDOWN_RIGHT] * self->vel;
		float tempy = self->dirY[mlDOWN_RIGHT] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
		self->y += tempy;
		self->dirMiddle = mlDOWN_RIGHT;
	}
	else if (self->activeDOWN) {

		float tempx = self->dirX[mlDOWN] * self->vel;
		float tempy = self->dirY[mlDOWN] * self->vel;

		if (sampleCollision(colid, self->x+tempx, self->y+tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }
		
		self->x += tempx,
		self->y += tempy;
		self->dirMiddle = mlDOWN;
	}
	else if (self->activeRIGHT) {
		float tempx = self->dirX[mlRIGHT] * self->vel;
		float tempy = self->dirY[mlRIGHT] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
			self->y += tempy;
		self->dirMiddle = mlRIGHT;
	}
	else if (self->activeUP) {

		float tempx = self->dirX[mlUP] * self->vel;
		float tempy = self->dirY[mlUP] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
			self->y += tempy;
		self->dirMiddle = mlUP;
	}
	else if (self->activeLEFT) {
		float tempx = self->dirX[mlLEFT] * self->vel;
		float tempy = self->dirY[mlLEFT] * self->vel;

		if (sampleCollision(colid, self->x + tempx, self->y + tempy, selfcolid->width, selfcolid->height)) { tempx = 0, tempy = 0; }

		self->x += tempx,
		self->y += tempy;
		self->dirMiddle = mlLEFT;
	}

}


// argumentos: <X, Y>
class mlMovimentAuto : public mlMovimentInstanceWithGhost {
public:
	float fX=0, fY=0, fH=0,
		  dX=0, dY=0, dH=0,
		  vuX=0, vuY=0, vel = 0;
	bool stop = true;
	sint dirMiddle = 0, dirCenter = 0;

	mlMovimentAuto(float x, float y, sint traceSize = 0, sint traceDelay = 0) : mlMovimentInstanceWithGhost(x, y, traceSize, traceDelay) {
		debugLog("created obj <mlMovimentAuto>");
		debugLog("position X:",x,"Y:",y);
	}

	~mlMovimentAuto() { debugLog("destructing obj <mlMovimentAuto>"); }

};

// metodo para modificar a velocidade
void mlVelocity(mlMovimentAuto *self, float vel) {
	if (self->dX && vel != self->vel) {
		self->vel=vel;
		self->vuX = self->vel / self->dH*self->dX;
		self->vuY = self->vel / self->dH*self->dY; //divisao por 0
	}
}
// metodo para modificar a direcao de movimeto
void mlDirection(mlMovimentAuto *self, float x, float y, float vel) {

	if (x == self->x && y == self->y) return;

	self->vel=vel;
	self->stop = false;
	
	self->dX = x - self->x, self->dY = y - self->y;
	self->fX = x, self->fY = y;

	self->fH = hypot(x, y);
	self->dH = hypot(self->dX, self->dY);

	self->vuX = self->vel / self->dH*self->dX+0.000001;
	self->vuY = self->vel / self->dH*self->dY+0.000001;
	x = self->dX, y = self->dY;

	sint tmpDir=99;

	if (y > x > 0) tmpDir = mlDOWN;
	if (x > y > 0) tmpDir = mlRIGHT;
	if (y < x < 0) tmpDir = mlUP;
	if (x < y < 0) tmpDir = mlLEFT;
	if (0 < -x < y) tmpDir = mlDOWN;
	if (0 < -y < x) tmpDir = mlRIGHT;
	if (0 > -x > y) tmpDir = mlUP;
	if (0 > -y > x) tmpDir = mlLEFT;
	if (tmpDir) self->dirCenter = tmpDir;

	if (x > 0 && y > 0) tmpDir = mlDOWN_RIGHT;
	if (x < 0 && y < 0) tmpDir = mlUP_LEFT;
	if (x < 0 && y > 0) tmpDir = mlDOWN_LEFT;
	if (x > 0 && y < 0) tmpDir = mlUP_RIGHT;
	if (tmpDir) self->dirMiddle = tmpDir;
}

// metodo para movimentar
void mlRun(mlMovimentAuto *self) {
	short int tmpRun=1;
	tmpRun *= !(self->vuX > 0 && self->x >= self->fX);
	tmpRun *= !(self->vuX < 0 && self->x <= self->fX);
	tmpRun *= !(self->vuY > 0 && self->y >= self->fY);
	tmpRun *= !(self->vuY < 0 && self->y <= self->fY);
	self->x += self->vuX * tmpRun, self->y += self->vuY *tmpRun;
	self->stop = !tmpRun;
}
#endif