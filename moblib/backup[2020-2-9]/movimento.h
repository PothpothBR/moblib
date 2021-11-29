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

typedef unsigned short int usint;
typedef  short int sint;

constexpr usint MOVIMENT_W = 0;
constexpr usint MOVIMENT_A = 1;
constexpr usint MOVIMENT_S = 2;
constexpr usint MOVIMENT_D = 3;

constexpr usint MOVIMENT_WA = 4;
constexpr usint MOVIMENT_WD = 5;
constexpr usint MOVIMENT_SA = 6;
constexpr usint MOVIMENT_SD = 7;

struct SpriteMovimentStance {
private:

	float *traceX;
	float *traceY ;

	usint traceSize;
	usint traceDelay;
	usint traceDelayCount;

public:
	float x, y;
	bool colid = false;

	

	SpriteMovimentStance(float x, float y, usint traceSize=0, usint traceDelay=0) {
		this->x = x;
		this->y = y;
		debugLog("created obj <SpriteMovimentStance>");
		debugLog("position X:", x, "Y:", y);
		debugLog("size of trace:", traceSize);
		debugLog("trace delay:", traceDelay);
		if (traceSize) {
			this->traceX = (float *)calloc(traceSize, sizeof(float));
			this->traceY = (float *)calloc(traceSize, sizeof(float));

			for (int i = 0; i < traceSize;i++) {
				traceX[i] = x;
				traceY[i] = y;
			}

		}
		else {
			this->traceX = nullptr;
			this->traceY = nullptr;
		}
		this->traceSize = traceSize;
		this->traceDelay = traceDelay;
		this->traceDelayCount = traceDelay;
	}

	void setTrace(float x,float y){
		if (traceSize <= 0) return;

		for (usint i = traceSize-1,i2 = traceSize-2;i > 0;i--,i2--) {
			
			traceX[i] = traceX[i2];
			traceY[i] = traceY[i2];
		}
		
		traceX[0] = x;
		traceY[0] = y;

	}

	float getTraceX(usint index) { if (index < traceSize) return traceX[index];  return -100; }
	float getTraceY(usint index) { if (index < traceSize) return traceY[index];  return -100; }

	void setAutoXY(float x,float y) {
		this->x = x;
		this->y = y;
		if (traceDelayCount > 1) {
			traceDelayCount--;
			return;
		}
		
		traceDelayCount = traceDelay;
		setTrace(x, y);

	}

	void setAutoTrace() {
		if (traceDelayCount > 1) {
			traceDelayCount--;
			return;
			
		}
		traceDelayCount = traceDelay;
		setTrace(x, y);
		
	}

	~SpriteMovimentStance(){
		debugLog("destructing obj <SpriteMovimentStance>"); 
		if (traceX) free(traceX);
		if (traceY) free(traceY);
	}
};


struct SpriteMovimentKeys : public SpriteMovimentStance{
private:
	static const float dirX[];
	static const float dirY[];
public:
	float vel = 0;

	bool stop = false;

	bool activeUP = false;
	bool activeDOWN = false;
	bool activeLEFT = false;
	bool activeRIGHT = false;

	float getDirX(usint index) { if (index < 8) return dirX[index]; return 0; }
	float getDirY(usint index) { if (index < 8) return dirY[index]; return 0; }

	SpriteMovimentKeys(float x, float y, usint vel = 0,usint traceSize = 0,usint traceDelay = 0): SpriteMovimentStance(x, y, traceSize, traceDelay) {
		debugLog("created obj <SpriteMovimentKeys>");
		debugLog("position X:", x, "Y:", y);
		debugLog("velocity:", vel);
		this->vel=vel;
	}


	~SpriteMovimentKeys() {
		debugLog("destructing obj <SpriteMovimentKeys>");
	}
};

const float SpriteMovimentKeys::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
const float SpriteMovimentKeys::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };

// metodo para movimentar
void run(SpriteMovimentKeys *self) {
	if (self->stop)	return;

	if (self->activeUP && self->activeLEFT)
		self->x += self->getDirX(MOVIMENT_WA) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_WA) * self->vel * !self->colid;
	else if (self->activeUP && self->activeRIGHT)
		self->x += self->getDirX(MOVIMENT_WD) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_WD) * self->vel * !self->colid;
	else if (self->activeDOWN && self->activeLEFT)
		self->x += self->getDirX(MOVIMENT_SA) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_SA) * self->vel * !self->colid;
	else if (self->activeDOWN && self->activeRIGHT)
		self->x += self->getDirX(MOVIMENT_SD) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_SD) * self->vel * !self->colid;

	else if (self->activeDOWN)
		self->x += self->getDirX(MOVIMENT_S) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_S) * self->vel * !self->colid;
	else if (self->activeRIGHT)
		self->x += self->getDirX(MOVIMENT_D) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_D) * self->vel * !self->colid;
	else if (self->activeUP)
		self->x += self->getDirX(MOVIMENT_W) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_W) * self->vel * !self->colid;
	else if (self->activeLEFT)
		self->x += self->getDirX(MOVIMENT_A) * self->vel * !self->colid,
		self->y += self->getDirY(MOVIMENT_A) * self->vel * !self->colid;
}


struct SpriteMovimentClick : public SpriteMovimentStance {
	
	bool activeLEFT = false;
	bool activeRIGHT = false;
	bool activeMIDDLE = false;

	bool activeMOVING = false;

	SpriteMovimentClick(float x, float y,usint traceSize = 0, usint traceDelay = 0) : SpriteMovimentStance(x, y, traceSize, traceDelay) {
		debugLog("created obj <SpriteMovimentClick>");
		debugLog("position X:", x, "Y:", y);
	}


	~SpriteMovimentClick() {
		debugLog("destructing obj <SpriteMovimentClick>");
	}
};


// argumentos: <X, Y>
struct SpriteMoviment : public SpriteMovimentStance {
	float fX=0, fY=0, fH=0,
		  dX=0, dY=0, dH=0,
		  vuX=0, vuY=0,
		  vel = 0;

	bool stop = false;

	usint dirMiddle = 0,
		  dirCloser = 0;

	SpriteMoviment(float x, float y, usint traceSize = 0, usint traceDelay = 0) : SpriteMovimentStance(x, y, traceSize, traceDelay) {
		debugLog("created obj <SpriteMoviment>");
		debugLog("position X:",x,"Y:",y);
	}

	~SpriteMoviment() { debugLog("destructing obj <SpriteMoviment>"); }

};

// metodo para modificar a velocidade
void velocity(SpriteMoviment *self, float vel) {
	if (self->dX && vel != self->vel) {
		self->vel=vel;
		self->vuX = self->vel / self->dH*self->dX;
		self->vuY = self->vel / self->dH*self->dY; //divisao por 0
	}
}
// metodo para modificar a direcao de movimeto
void direction(SpriteMoviment *self, float x, float y, float vel) {

	if (x == self->x && y == self->y) return;

	self->vel=vel;
	self->stop = false;
	
	self->dX = x - self->x, self->dY = y - self->y;
	self->fX = x, self->fY = y;

	self->fH = hypot(x, y);
	self->dH = hypot(self->dX, self->dY);

	self->vuX = self->vel / self->dH*self->dX; //divisao por 0
	self->vuY = self->vel / self->dH*self->dY;

	x = self->dX, y = self->dY;

	usint tmpDir;

	if (y > x > 0) tmpDir = MOVIMENT_S;
	if (x > y > 0) tmpDir = MOVIMENT_D;
	if (y < x < 0) tmpDir = MOVIMENT_W;
	if (x < y < 0) tmpDir = MOVIMENT_A;
	if (0 < -x < y) tmpDir = MOVIMENT_S;
	if (0 < -y < x) tmpDir = MOVIMENT_D;
	if (0 > -x > y) tmpDir = MOVIMENT_W;
	if (0 > -y > x) tmpDir = MOVIMENT_A;
	if (tmpDir) self->dirCloser = tmpDir;

	if (x > 0 && y > 0) tmpDir = MOVIMENT_SD;
	if (x < 0 && y < 0) tmpDir = MOVIMENT_WA;
	if (x < 0 && y > 0) tmpDir = MOVIMENT_SA;
	if (x > 0 && y < 0) tmpDir = MOVIMENT_WD;
	if (tmpDir) self->dirMiddle = tmpDir;
}

// metodo para movimentar
void run(SpriteMoviment *self) {

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