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
  | 			  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------*/
#ifndef FORMAT_H
#define FORMAT_H

//#include <cstdlib>
#include "debug_log.h"
#include <cmath>
#include "moviment.h"

 
typedef  short int sint;

// argumentos: <mlMovimentAuto *, mlSheet *>
struct mlFormat {
public:
	mlFormat* next = nullptr;
	static mlFormat* head;
	static sint queueSize;
	float *x, *y,
		  width, height;
	bool *colid = nullptr;

	mlFormat(mlMovimentInstance* selfMoviment, mlSheet *selfSheet) {
		debugLog("created obj <mlFormat>");
		debugLog("queue size:", queueSize + 1);
		this->x = &selfMoviment->x;
		this->y = &selfMoviment->y;
		this->colid = &selfMoviment->colid;
		this->width = selfSheet->cellWidth;
		this->height = selfSheet->cellHeight;
		debugLog("X:", (sint)*x, "Y:", (sint)*y);
		debugLog("Width:", (sint)width, "Height:", (sint)height);

		this->next = head;
		this->head = this;
		queueSize++;
	}

	mlFormat(mlMovimentInstance* selfMoviment, float width, float height) {
		debugLog("created obj <mlFormat>");
		debugLog("queue size:", queueSize + 1);
		this->x = &selfMoviment->x;
		this->y = &selfMoviment->y;
		this->colid = &selfMoviment->colid;
		this->width = width;
		this->height = height;
		debugLog("X:", (sint)* x, "Y:", (sint)* y);
		debugLog("Width:", (sint)width, "Height:", (sint)height);

		this->next = head;
		this->head = this;
		queueSize++;
	}

	~mlFormat() {
		debugLog("destructing obj <mlFormat>");
		queueSize--;
	}

};

mlFormat* mlFormat::head = nullptr;
sint mlFormat::queueSize = 0;

//testa a colisao de quadrados entre um objeto <form> e os outros objetos <form>
void mlIsolatedCollision(mlFormat *self) {

	float x1 = *self->x, y1 = *self->y, w1 = self->width, h1 = self->height;

	for (mlFormat *selfver = self->head;selfver;selfver = selfver->next) {

		if (selfver == self) continue;

		float
			x2 = *selfver->x, y2 = *selfver->y, w2 = selfver->width, h2 = selfver->height;

		if(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
			*self->colid = true;
		}else{
			*self->colid = false;
		}
	}
}

bool mlIsolatedCollision(mlFormat *self, float x, float y, float w, float h) {

	float x1 = *self->x, y1 = *self->y, w1 = self->width, h1 = self->height;

	float x2 = x, y2 = y, w2 = w, h2 = h;

	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2){
		*self->colid = true; return true;
	}else{
		*self->colid = false; return false;
	}

}

bool mlIsolatedCollision(mlFormat * self, mlFormat * self2)
{

	float x1 = *self->x, y1 = *self->y, w1 = self->width, h1 = self->height;

	if (self == self2) return false;

	float x2 = *self2->x, y2 = *self2->y, w2 = self2->width, h2 = self2->height;

	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2){
		*self->colid = true;
		return true;
	}else{
		*self->colid = false;
		return false;
	}
}

//testa a colisao de quadrados entre todos os objetos <form>
void mlCollision(mlFormat *self) {

	mlFormat *head = self->head;

	for (self = head;self;self = self->next) {

		float x1 = *self->x, y1 = *self->y, w1 = self->width, h1 = self->height;

		for (mlFormat *selfver = head;selfver;selfver = selfver->next) {

			if (selfver == self) continue;

			float x2 = *selfver->x,y2 = *selfver->y, w2 = selfver->width, h2 = selfver->height;

			if(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
				*self->colid = true;
			}else{
				*self->colid = false;
			}
		}
	}
}

#endif

