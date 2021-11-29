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

typedef unsigned short int usint;

// macros para definir a direcao
#define  MOVIMENT_DIRW  1;
#define  MOVIMENT_DIRA  2;
#define  MOVIMENT_DIRS  4;
#define  MOVIMENT_DIRD  7;

#define  MOVIMENT_DIRWA  10;
#define  MOVIMENT_DIRWD  13;
#define  MOVIMENT_DIRSA  16;
#define  MOVIMENT_DIRSD  19;

/*struct SpriteMovimentKeys {

	float x, y,
		  vuX, vuY,
		  vel;

	bool finsh = false,
		 colid = false;
	usint dirMiddle = 0,
		  dirCloser = 0;

	explicit SpriteMovimentKeys(float x, float y) {
		debugLog("created obj <SpriteMovimentKeys>");
		debugLog("position X:", x, "Y:", y);
		this->colid = false;
		this->x = x, this->y = y;

		this->dX = x - this->x,
		this->dY = y - this->y;
		this->fX = x,
		this->fY = y;

		this->fH = hypot(x, y);
		this->dH = hypot(this->dX, this->dY);

		this->vuX = this->vel / this->dH*self->dX + 1;
		this->vuY = this->vel / this->dH*self->dY + 1;

		x = self->dX, y = self->dY;

	}

	~SpriteMovimentKeys() { debugLog("destructing obj <SpriteMovimentKeys>"); }
};
*/
// argumentos: <X, Y>
struct SpriteMoviment {

	float x, y,
		  fX, fY, fH,
		  dX, dY, dH,
		  vuX, vuY,
		  vel;

	bool finsh = false,
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
	if (self->dX) {
		self->vel = vel;
		self->vuX = self->vel / self->dH*self->dX;
		self->vuY = self->vel / self->dH*self->dY; //divisao por 0
	}
}
// metodo para modificar a direcao de movimeto
void direction(SpriteMoviment *self, float x, float y, float vel) {

	if (x == self->x && y == self->y) return;

	self->vel = vel;
	self->finsh = false;
	
	self->dX = x - self->x, self->dY = y - self->y;
	self->fX = x, self->fY = y;

	self->fH = hypot(x, y);
	self->dH = hypot(self->dX, self->dY);

	self->vuX = self->vel / self->dH*self->dX; //divisao por 0
	self->vuY = self->vel / self->dH*self->dY;

	x = self->dX, y = self->dY;

	usint tmpDir;

	if (y > x > 0) tmpDir = 4;
	if (x > y > 0) tmpDir = 7;
	if (y < x < 0) tmpDir = 1;
	if (x < y < 0) tmpDir = 2;
	if (0 < -x < y) tmpDir = 4;
	if (0 < -y < x) tmpDir = 7;
	if (0 > -x > y) tmpDir = 1;
	if (0 > -y > x) tmpDir = 2;
	if (tmpDir) self->dirCloser = tmpDir;

	if (x > 0 && y > 0) tmpDir = 19;
	if (x < 0 && y < 0) tmpDir = 10;
	if (x < 0 && y > 0) tmpDir = 16;
	if (x > 0 && y < 0) tmpDir = 13;
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
	self->finsh = !tmpRun * !self->colid;
}

/*void run(SpriteMovimentKeys* self) {

	self->x += self->vuX * tmpRun, self->y += self->vuY *tmpRun;

}*/

#endif