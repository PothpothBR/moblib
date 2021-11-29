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
#include "colision.h"
#include "position.h"
 
typedef short int sint;

namespace MOB_MOVIMENT {

	constexpr bool ALL_DIRECTION = true;
	constexpr bool AXIS_DIRECTION = false;

	constexpr sint UP = 0;
	constexpr sint LEFT = 1;
	constexpr sint DOWN = 2;
	constexpr sint RIGHT = 3;

	constexpr sint UP_LEFT = 4;
	constexpr sint UP_RIGHT = 5;
	constexpr sint DOWN_LEFT = 6;
	constexpr sint DOWN_RIGHT = 7;
	
	class POSITION_GHOST : public MOB_POSITION {
	public:
		float *trace_X, *trace_Y;
		sint trace_size, trace_delay, trace_delay_count;

		POSITION_GHOST(float x, float y, sint trace_size = 0, sint trace_delay = 0) : MOB_POSITION(x, y) {
			if (trace_size) {
				this->trace_X = (float *)calloc(trace_size, sizeof(float));
				this->trace_Y = (float *)calloc(trace_size, sizeof(float));
				for (int i = 0; i < trace_size;i++) { trace_X[i] = x, trace_Y[i] = y; }
			}
			else { this->trace_X = nullptr, this->trace_Y = nullptr; }
			this->trace_size = trace_size, this->trace_delay = trace_delay, this->trace_delay_count = trace_delay;
		}
	
		~POSITION_GHOST() {
			if (trace_X) free(trace_X); if (trace_Y) free(trace_Y);
		}
	};

	// classe para movimentacao com teclado flags: MOB_POSITION | MOB_MOVIMENT::POSITION_GHOST
	template <class T>
	class KEYBOARD{
	public:
		static const double dirX[8];
		static const double dirY[8];
		sint dirMiddle = 2;
		float vel = 0;
		bool UP = false, DOWN = false, LEFT = false, RIGHT = false;
		T* position = nullptr;
		
		KEYBOARD(T* position, float vel = 0) { this->position = position, this->vel = vel; }
		~KEYBOARD() { if (position) { delete position; position = nullptr; } }
	};

	const double KEYBOARD<POSITION_GHOST>::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const double KEYBOARD<POSITION_GHOST>::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };
	const double KEYBOARD<MOB_POSITION>::dirX[8] = { 0, -1,  0,  1, -0.707107 ,  0.707107, -0.707107 ,  0.707107 };
	const double KEYBOARD<MOB_POSITION>::dirY[8] = { -1,  0,  1,  0, -0.707107 , -0.707107,  0.707107 ,  0.707107 };

	// argumentos: <X, Y>
	template <class T>
	class AUTO{
	public:
		float fX = 0, fY = 0, fH = 0,
			dX = 0, dY = 0, dH = 0,
			vuX = 0, vuY = 0, vel = 0;
		bool stop = true;
		sint dirMiddle = 0, dirExact = 0;
		T* position = nullptr;

		AUTO(T* position){ this->position = position, this->vel = vel; }
		~AUTO() { if (position){ delete position; position = nullptr; } }
	};

	template <class T>
	class MOUSE {
	public:
		T* position = nullptr;
		bool LEFT = false, RIGTH = false, CENTER = false, MOVING = false;

		MOUSE(T* position) { this->position = position;  }
		MOUSE() {}

		~MOUSE() { if (position){ delete position; position = nullptr; } }
	};

	template <class T>
	class TOUCH {
	public:
		T* position = nullptr;
		bool ACTIVE[5] = { false }, MOVING = false;

		TOUCH(T* position) { this->position = position; }
		~TOUCH() { if (position) { delete position; position = nullptr; } }
	};
}

using namespace MOB_MOVIMENT;

float mob_get_moviment_trace_X(POSITION_GHOST* self, sint index) { if (index < self->trace_size) return self->trace_X[index];  return -100; }
float mob_get_moviment_trace_Y(POSITION_GHOST* self, sint index) { if (index < self->trace_size) return self->trace_Y[index];  return -100; }

void mob_set_moviment_trace(POSITION_GHOST* self, float x, float y) {
	if (self->trace_size <= 0) return;
	for (sint i = self->trace_size - 1, i2 = self->trace_size - 2; i > 0; i--, i2--) { self->trace_X[i] = self->trace_X[i2], self->trace_Y[i] = self->trace_Y[i2]; }
	self->trace_X[0] = x, self->trace_Y[0] = y;
}

void mob_set_auto_trace_xy(POSITION_GHOST* self, float x, float y) {
	self->x = x, self->y = y;
	if (self->trace_delay_count > 1) { self->trace_delay_count--; return; }
	self->trace_delay_count = self->trace_delay;
	mob_set_moviment_trace(self, x, y);
}

void mob_set_auto_trace(POSITION_GHOST* self) {
	if (self->trace_delay_count > 1) { self->trace_delay_count--; return; }
	self->trace_delay_count = self->trace_delay;
	mob_set_moviment_trace(self, self->x, self->y);
}

// metodo para movimentar
template <class T>
void mob_run(KEYBOARD<T>* self, bool all = true) {

	if (self->UP && self->LEFT && all) {
		self->position->x += self->dirX[UP_LEFT] * self->vel,
			self->position->y += self->dirY[UP_LEFT] * self->vel;
		self->dirMiddle = UP_LEFT;
	}
	else if (self->UP && self->RIGHT && all) {
		self->position->x += self->dirX[UP_RIGHT] * self->vel,
			self->position->y += self->dirY[UP_RIGHT] * self->vel;
		self->dirMiddle = UP_RIGHT;
	}
	else if (self->DOWN && self->LEFT && all) {
		self->position->x += self->dirX[DOWN_LEFT] * self->vel,
			self->position->y += self->dirY[DOWN_LEFT] * self->vel;
		self->dirMiddle = DOWN_LEFT;
	}
	else if (self->DOWN && self->RIGHT && all) {
		self->position->x += self->dirX[DOWN_RIGHT] * self->vel,
			self->position->y += self->dirY[DOWN_RIGHT] * self->vel;
		self->dirMiddle = DOWN_RIGHT;
	}
	else if (self->DOWN) {
		self->position->x += self->dirX[DOWN] * self->vel,
			self->position->y += self->dirY[DOWN] * self->vel;
		self->dirMiddle = DOWN;
	}
	else if (self->RIGHT) {
		self->position->x += self->dirX[RIGHT] * self->vel,
			self->position->y += self->dirY[RIGHT] * self->vel;
		self->dirMiddle = RIGHT;
	}
	else if (self->UP) {

		self->position->x += self->dirX[UP] * self->vel,
			self->position->y += self->dirY[UP] * self->vel;
		self->dirMiddle = UP;
	}
	else if (self->LEFT) {
		self->position->x += self->dirX[LEFT] * self->vel,
			self->position->y += self->dirY[LEFT] * self->vel;
		self->dirMiddle = LEFT;
	}

}

// metodo para movimentar, com sistema de colizao auto implementado
template <class T>
void mob_run(KEYBOARD<T>* self, MOB_COLLISION::COLID* self_box, MOB_FORM* another_box, int obj_in_out, bool all = true) {
	mob_reload_collision(self_box);
	mob_run(self, all);
	mob_collision(self_box, another_box, obj_in_out);
}

// metodo para movimentar, com sistema de colizao com multiplos objetos auto implementado
template <class T>
void mob_run(KEYBOARD<T>* self, MOB_COLLISION::COLID* self_box, MOB_FORM_CHAIN* list_box, int obj_in_out, bool all = true) {
	mob_reload_collision(self_box);
	mob_run(self, all);
	mob_collision(self_box, list_box, obj_in_out);
}

// recarrega a colizao de um objeto colizor a partir da movimentacao de outro objeto
template <class T>
void mob_reload_colision_mirror(KEYBOARD<T>* self, MOB_COLLISION::COLID* self_box, bool all = true) {
	if (self->UP && self->LEFT && all) {
		self_box->trail.x = self_box->form.position->x + self->dirX[UP_LEFT] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[UP_LEFT] * self->vel;
	}												   
	else if (self->UP && self->RIGHT && all) {		   
		self_box->trail.x = self_box->form.position->x + self->dirX[UP_RIGHT] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[UP_RIGHT] * self->vel;
	}												   
	else if (self->DOWN && self->LEFT && all) {		   
		self_box->trail.x = self_box->form.position->x + self->dirX[DOWN_LEFT] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[DOWN_LEFT] * self->vel;
	}												   
	else if (self->DOWN && self->RIGHT && all) {	   
		self_box->trail.x = self_box->form.position->x + self->dirX[DOWN_RIGHT] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[DOWN_RIGHT] * self->vel;
	}												   
	else if (self->DOWN) {							   
		self_box->trail.x = self_box->form.position->x + self->dirX[DOWN] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[DOWN] * self->vel;
	}												   
	else if (self->RIGHT) {							   
		self_box->trail.x = self_box->form.position->x + self->dirX[RIGHT] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[RIGHT] * self->vel;
	}												  
	else if (self->UP) {							   
		self_box->trail.x = self_box->form.position->x + self->dirX[UP] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[UP] * self->vel;
	}												   
	else if (self->LEFT) {							   
		self_box->trail.x = self_box->form.position->x + self->dirX[LEFT] * self->vel;
		self_box->trail.y = self_box->form.position->y + self->dirY[LEFT] * self->vel;
	}
}

template <class T>
void mob_reload_colision_mirror(AUTO<T>* self, MOB_COLLISION::COLID* self_box) {
	if (!self->stop) {
		self_box->trail.x = self->vuX;
		self_box->trail.y = self->vuY;
	}
}

// metodo para modificar a velocidade
template <class T>
void mob_velocity(AUTO<T>* self, float vel) {
	if (self->dX && vel != self->vel) {
		self->vel = vel;
		self->vuX = self->vel / self->dH * self->dX;
		self->vuY = self->vel / self->dH * self->dY; //divisao por 0
	}
}
// metodo para modificar a direcao de movimeto
template <class T>
void mob_direction(AUTO<T>* self, float x, float y, float vel) {

	if (x == self->position->x && y == self->position->y) return;

	self->vel = vel;
	self->stop = false;

	self->dX = x - self->position->x, self->dY = y - self->position->y;
	self->fX = x, self->fY = y;

	self->fH = hypot(x, y);
	self->dH = hypot(self->dX, self->dY);

	self->vuX = self->vel / self->dH * self->dX + 0.000001;
	self->vuY = self->vel / self->dH * self->dY + 0.000001;
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
void mob_run(AUTO<T>* self) {
	short int tmpRun = 1;
	tmpRun *= !(self->vuX > 0 && self->position->x >= self->fX);
	tmpRun *= !(self->vuX < 0 && self->position->x <= self->fX);
	tmpRun *= !(self->vuY > 0 && self->position->y >= self->fY);
	tmpRun *= !(self->vuY < 0 && self->position->y <= self->fY);
	self->position->x += self->vuX * tmpRun, self->position->y += self->vuY * tmpRun;
	self->stop = !tmpRun;
}
#endif