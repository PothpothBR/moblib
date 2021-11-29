/*


						----------------------------------------------------
						|               Programa feito por                 |
						|     [Bruno Dalagnol] [2018] [versao: sei la]     |
						----------------------------------------------------
						|                                                  |
						|			  /\         /\       ___              |
						|			 /--\_______/--\     /  _|             |
						|			 |  Y       Y  |    / /                |
						|			 |    ==T==    |   / /                 |
						|			 \_____________/  / /                  |
						|				|  _____   \ / /                   |
						|				|           \ /                    |
						|				|  |--|  |\  |                     |
						|				|__||_|__||__|                     |
						----------------------------------------------------



	||||||    ||||||    ||||||			||||||    ||||||   |     |  ||     |    ||||||			||||||
	|    |   |      |   |     |			|     |   |     |  |     |  | |    |   |      |			|     |
	|    |  |        |  |     |			|     |   |     |  |     |  |  |   |  |        |		|      |
	|||||   |        |  | |||||			||||||    | |||||  |     |  |   |  |  |        |		|      |
	|       |        |  |  |			|     |   |  |     |     |  |    | |  |        |		|      |
	|        |      |   |   |			|     |   |   |    |	 |  |     ||   |      |			|     |
	|         ||||||    |    |			|||||||   |    |   |||||||  |      |    ||||||			||||||   |||

	*/
#ifndef MOVIMENT_H
#define MOVIMENT_H

//uso esclusivo para a hipotenusa
#include <cmath>

#include "debug_log.h"

typedef unsigned short int usint;
typedef  short int sint;

constexpr usint MOVIMENT_DIRW = 0;
constexpr usint MOVIMENT_DIRA = 1;
constexpr usint MOVIMENT_DIRS = 2;
constexpr usint MOVIMENT_DIRD = 3;

constexpr usint MOVIMENT_DIRWA = 4;
constexpr usint MOVIMENT_DIRWD = 5;
constexpr usint MOVIMENT_DIRSA = 6;
constexpr usint MOVIMENT_DIRSD = 7;

struct SpriteMovimentKeys {
private:
	float vel=0;

	const float dirX[8] = {  0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const float dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };

	bool colid = false;
public:
	float 
		vuX = 0, vuY = 0,
		x, y;
	bool stop = false;

	float getVel() { return vel; }
	float getDirX(usint index) { if (index < 8) return dirX[8]; return 0; }
	float getDirY(usint index) { if (index < 8) return dirY[8]; return 0; }
	bool getColid() { return colid; }

	void setColid(bool val) { colid = val; }
	void setVel(float val) { vel = val; }

	explicit SpriteMovimentKeys(float x, float y) {
		debugLog("created obj <SpriteMovimentKeys>");
		debugLog("position X:", x, "Y:", y);
		debugLog("velocity:", vel);
		this->colid = false;
		this->x = x, this->y = y;
	}


	~SpriteMovimentKeys() { debugLog("destructing obj <SpriteMovimentKeys>"); }
};

// metodo para modificar a velocidade
void velocity(SpriteMovimentKeys *self, float vel) {
	if (vel != self->getVel()) {
		self->vuX /= self->getVel();
		self->vuY /= self->getVel();
		self->setVel(vel);
		self->vuX *= vel;
		self->vuY *= vel;
	}
}

void direction(SpriteMovimentKeys *self,usint dir, float vel) {

	self->setVel(vel);
	self->stop = false;
	if (0 <= dir < 8) {
		self->vuX = self->getDirX(dir) * vel;
		self->vuY = self->getDirY(dir) * vel;
	}
}

void run(SpriteMovimentKeys *self) {
	if (self->stop) {
		self->stop = false;
		return;
	}
	self->x += self->vuX * !self->getColid(),
	self->y += self->vuY * !self->getColid();

}


// argumentos: <X, Y>
struct SpriteMoviment {

	float x, y,
		  fX=0, fY=0, fH=0,
		  dX=0, dY=0, dH=0,
		  vuX=0, vuY=0,
		  vel=0;

	bool stop = false,
		 colid = false;

	usint dirMiddle = 0,
		  dirCloser = 0;

	explicit SpriteMoviment(float x, float y) {
		debugLog("created obj <SpriteMoviment>");
		debugLog("position X:",x,"Y:",y);
		this->colid = false;
		this->x = x, this->y = y;
	}

	~SpriteMoviment() { debugLog("destructing obj <SpriteMoviment>"); }

};

// metodo para modificar a velocidade
void velocity(SpriteMoviment *self, float vel) {
	if (self->dX && vel != self->vel) {
		self->vel = vel;
		self->vuX = self->vel / self->dH*self->dX;
		self->vuY = self->vel / self->dH*self->dY; //divisao por 0
	}
}
// metodo para modificar a direcao de movimeto
void direction(SpriteMoviment *self, float x, float y, float vel) {

	if (x == self->x && y == self->y) return;

	self->vel = vel;
	self->stop = false;
	
	self->dX = x - self->x, self->dY = y - self->y;
	self->fX = x, self->fY = y;

	self->fH = hypot(x, y);
	self->dH = hypot(self->dX, self->dY);

	self->vuX = self->vel / self->dH*self->dX; //divisao por 0
	self->vuY = self->vel / self->dH*self->dY;

	x = self->dX, y = self->dY;

	usint tmpDir;

	if (y > x > 0) tmpDir = MOVIMENT_DIRS;
	if (x > y > 0) tmpDir = MOVIMENT_DIRD;
	if (y < x < 0) tmpDir = MOVIMENT_DIRW;
	if (x < y < 0) tmpDir = MOVIMENT_DIRA;
	if (0 < -x < y) tmpDir = MOVIMENT_DIRS;
	if (0 < -y < x) tmpDir = MOVIMENT_DIRD;
	if (0 > -x > y) tmpDir = MOVIMENT_DIRW;
	if (0 > -y > x) tmpDir = MOVIMENT_DIRA;
	if (tmpDir) self->dirCloser = tmpDir;

	if (x > 0 && y > 0) tmpDir = MOVIMENT_DIRSD;
	if (x < 0 && y < 0) tmpDir = MOVIMENT_DIRWA;
	if (x < 0 && y > 0) tmpDir = MOVIMENT_DIRSA;
	if (x > 0 && y < 0) tmpDir = MOVIMENT_DIRWD;
	if (tmpDir) self->dirMiddle = tmpDir;

	return;
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