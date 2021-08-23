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

// macros para definir a direcao
constexpr usint dirW = 1;
constexpr usint dirA = 2;
constexpr usint dirS = 4;
constexpr usint dirD = 7;

constexpr usint dirWA = 10;
constexpr usint dirWD = 13;
constexpr usint dirSA = 16;
constexpr usint dirSD = 19;


// estrutura de movimentacao
struct SpriteMoviment {

	float x, y, f_x, f_y, f_h, d_x, d_y, d_h;
	float vu_x, vu_y, vel;
	bool stop = false;
	usint dir[2] = { 0, 0 };
	explicit SpriteMoviment(short int x, short int y) {
		debugLog("created obj <Moviment>");
		debugLog("position X:",x," Y:",y);

		this->x = x, this->y = y;
	}

	~SpriteMoviment() {
		debugLog("destructing obj <Moviment>");
	}

};

// metodo para modificar a velocidade
void velocity(SpriteMoviment *self, short int vel) {
	if (self->d_x) {
		self->vel = vel;
		self->vu_x = self->vel / self->d_h*self->d_x;
		self->vu_y = self->vel / self->d_h*self->d_y;
	}
}
// metodo para modificar a direcao de movimeto
void direction(SpriteMoviment *self, short int x, short int y, short int vel) {

	if (x == self->x && y == self->y) return;

	self->vel = vel;
	self->stop = false;

	self->d_x = x - self->x, self->d_y = y - self->y;
	self->f_x = x, self->f_y = y;

	self->f_h = hypot((float)x, y);
	self->d_h = hypot(self->d_x, self->d_y);

	self->vu_x = self->vel / self->d_h*self->d_x;
	self->vu_y = self->vel / self->d_h*self->d_y;

	x = self->d_x, y = self->d_y;

	usint tmpDir;

	tmpDir = (y > x > 0) ? 4 : 0;
	tmpDir = (x > y > 0) ? 7 : 0;
	tmpDir = (y < x < 0) ? 1 : 0;
	tmpDir = (x < y < 0) ? 2 : 0;
	tmpDir = (0 < -x < y) ? 4 : 0;
	tmpDir = (0 < -y < x) ? 7 : 0;
	tmpDir = (0 > -x > y) ? 1 : 0;
	tmpDir = (0 > -y > x) ? 2 : 0;
	if (tmpDir) self->dir[0] = tmpDir;

	tmpDir = (x > 0 && y > 0) ? 19 : 0;
	tmpDir = (x < 0 && y < 0) ? 10 : 0;
	tmpDir = (x < 0 && y > 0) ? 16 : 0;
	tmpDir = (x > 0 && y < 0) ? 13 : 0;
	if (tmpDir) self->dir[1] = tmpDir;
}

void run(SpriteMoviment *self) {

	short int tmpRun0, tmpRun1, tmpRun2, tmpRun3;

	tmpRun0 = (int)(self->vu_x > 0 && self->x >= self->f_x);
	tmpRun1 = (int)(self->vu_x < 0 && self->x <= self->f_x);
	tmpRun2 = (int)(self->vu_y > 0 && self->y >= self->f_y);
	tmpRun3 = (int)(self->vu_y < 0 && self->y <= self->f_y);

	//implementar parada

	cout << tmpRun0 << '-' << tmpRun1 << '-' << tmpRun2 << '-' << tmpRun3 << endl;
	self->x += self->vu_x, self->y += self->vu_y ;
	self->stop = tmpRun0;
}

void collision(SpriteMoviment *self, SpriteMoviment *check) {

	(self->x < check->x) ? self->x-=self->vu_x : false;
	
}

#endif