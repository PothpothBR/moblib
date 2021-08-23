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

struct mlMovimentInstance {
public:
	float *traceX, *traceY ;
	sint traceSize, traceDelay, traceDelayCount;
	float x, y;
	bool colid = false;

	mlMovimentInstance(float x, float y, sint traceSize=0, sint traceDelay=0) {
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
	~mlMovimentInstance(){
		debugLog("destructing obj <mlMovimentInstance>"); 
		if (traceX) free(traceX); if (traceY) free(traceY);
	}
};

void setTrace(mlMovimentInstance *self, float x, float y) {
	if (self->traceSize <= 0) return;
	for (sint i = self->traceSize - 1, i2 = self->traceSize - 2;i > 0;i--, i2--) { self->traceX[i] = self->traceX[i2], self->traceY[i] = self->traceY[i2]; }
	self->traceX[0] = x, self->traceY[0] = y;
}

float getTraceX(mlMovimentInstance *self, sint index) { if (index < self->traceSize) return self->traceX[index];  return -100; }
float getTraceY(mlMovimentInstance *self, sint index) { if (index < self->traceSize) return self->traceY[index];  return -100; }

void setAutoXY(mlMovimentInstance *self, float x, float y) {
	self->x = x, self->y = y;
	if (self->traceDelayCount > 1) { self->traceDelayCount--; return; }
	self->traceDelayCount = self->traceDelay;
	setTrace(self, x, y);
}

void setAutoTrace(mlMovimentInstance *self) {
	if (self->traceDelayCount > 1) { self->traceDelayCount--; return; }
	self->traceDelayCount = self->traceDelay;
	setTrace(self, self->x, self->y);
}


struct mlMovimentKeys : public mlMovimentInstance {
public:
	static const float dirX[];
	static const float dirY[];
	sint dirMiddle = 2;
	float vel = 0;
	bool activeUP = false, activeDOWN = false, activeLEFT = false, activeRIGHT = false;

	mlMovimentKeys(float x, float y, float vel = 0,sint traceSize = 0,sint traceDelay = 0): mlMovimentInstance(x, y, traceSize, traceDelay) {
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
		self->x += self->dirX[mlUP_LEFT] * self->vel * !self->colid,
		self->y += self->dirY[mlUP_LEFT] * self->vel * !self->colid;
		self->dirMiddle = mlUP_LEFT;
	}
	else if (self->activeUP && self->activeRIGHT && all) {
		self->x += self->dirX[mlUP_RIGHT] * self->vel * !self->colid,
		self->y += self->dirY[mlUP_RIGHT] * self->vel * !self->colid;
		self->dirMiddle = mlUP_RIGHT;
	}
	else if (self->activeDOWN && self->activeLEFT && all) {
		self->x += self->dirX[mlDOWN_LEFT] * self->vel * !self->colid,
		self->y += self->dirY[mlDOWN_LEFT] * self->vel * !self->colid;
		self->dirMiddle = mlDOWN_LEFT;
	}
	else if (self->activeDOWN && self->activeRIGHT && all) {
		self->x += self->dirX[mlDOWN_RIGHT] * self->vel * !self->colid,
		self->y += self->dirY[mlDOWN_RIGHT] * self->vel * !self->colid;
		self->dirMiddle = mlDOWN_RIGHT;
	}
	else if (self->activeDOWN) {
		self->x += self->dirX[mlDOWN] * self->vel * !self->colid,
		self->y += self->dirY[mlDOWN] * self->vel * !self->colid;
		self->dirMiddle = mlDOWN;
	}
	else if (self->activeRIGHT) {
		self->x += self->dirX[mlRIGHT] * self->vel * !self->colid,
		self->y += self->dirY[mlRIGHT] * self->vel * !self->colid;
		self->dirMiddle = mlRIGHT;
	}
	else if (self->activeUP) {

		self->x += self->dirX[mlUP] * self->vel * !self->colid,
		self->y += self->dirY[mlUP] * self->vel * !self->colid;
		self->dirMiddle = mlUP;
	}
	else if (self->activeLEFT) {
		self->x += self->dirX[mlLEFT] * self->vel * !self->colid,
		self->y += self->dirY[mlLEFT] * self->vel * !self->colid;
		self->dirMiddle = mlLEFT;
	}

}


// argumentos: <X, Y>
struct mlMovimentAuto : public mlMovimentInstance {
	float fX=0, fY=0, fH=0,
		  dX=0, dY=0, dH=0,
		  vuX=0, vuY=0, vel = 0;
	bool stop = false;
	sint dirMiddle = 0, dirCenter = 0;

	mlMovimentAuto(float x, float y, sint traceSize = 0, sint traceDelay = 0) : mlMovimentInstance(x, y, traceSize, traceDelay) {
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
	tmpRun *= !self->colid;
	self->x += self->vuX * tmpRun, self->y += self->vuY *tmpRun;
	self->stop = !tmpRun * !self->colid;
}
#endif