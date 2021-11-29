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
#ifndef FORMAT_H
#define FORMAT_H

//#include <cstdlib>
#include "debug_log.h"
#include <cmath>
#include "moviment.h"

typedef unsigned short int usint;
typedef  short int sint;

#define FORMAT_COLIDON true
#define FORMAT_COLIDOFF false

#define FORMAT_RECTANGLE false
#define FORMAT_CIRCLE false

// argumentos: <mlMoviment *, mlSheet *>
struct mlFormat {
private:
	mlFormat* next = nullptr;
	static mlFormat* head;
	static usint queueSize;
	float *x, *y,
		  width, height;
	bool *colid = nullptr;
	bool colidState = FORMAT_COLIDON;

public:

	mlFormat* getNext() { return next; }
	mlFormat* getHead() { return head; }
	usint getQueueSize() { return queueSize; }

	float getX() { return *x; }
	float getY() { return *y; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	bool* getColid() { return colid; }
	bool  setColidState(bool verify) { colidState = verify; }
	bool  getColidState() { return colidState; }

	mlFormat(mlMoviment *selfMoviment, mlSheet *selfSheet) {
		debugLog("created obj <mlFormat>");
		debugLog("queue size:", queueSize+1);
		this->x = &selfMoviment->x;
		this->y = &selfMoviment->y;
		this->colid  = &selfMoviment->colid;
		this->width  =  selfSheet->getCellWidth();
		this->height =  selfSheet->getCellHeight();
		debugLog("X:",(usint)*x, "Y:", (usint)*y);
		debugLog("Width:", (usint)width, "Height:", (usint)height);

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
		debugLog("X:", (usint)* x, "Y:", (usint)* y);
		debugLog("Width:", (usint)width, "Height:", (usint)height);

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
usint mlFormat::queueSize = 0;

//testa a colisao de quadrados entre um objeto <form> e os outros objetos <form>
void isolatedCollision(mlFormat *self) {

	if (self->getColidState() == FORMAT_COLIDOFF) return;

	float
		x1 = self->getX(),
		y1 = self->getY(),
		w1 = self->getWidth(),
		h1 = self->getHeight();

	for (mlFormat *selfver = self->getHead();selfver;selfver = selfver->getNext()) {

		if (selfver == self) continue;

		float
			x2 = selfver->getX(),
			y2 = selfver->getY(),
			w2 = selfver->getWidth(),
			h2 = selfver->getHeight();

		if
			(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
			*self->getColid() = true;
		}
		else
		{
			*self->getColid() = false;
		}
	}
}

bool isolatedCollision(mlFormat * self, mlFormat * self2)
{

	if (self->getColidState() == FORMAT_COLIDOFF)
		return false;

	float x1 = self->getX(), y1 = self->getY(), w1 = self->getWidth(), h1 = self->getHeight();

	if (self == self2)
		return false;

	float x2 = self2->getX(), y2 = self2->getY(), w2 = self2->getWidth(), h2 = self2->getHeight();

	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)
	{
		*self->getColid() = true;
		return true;
	}
	else
	{
		*self->getColid() = false;
		return false;
	}
}

void testcriclcold(float x1, float y1, float r1, float x2, float y2, float r2) {

	float dx = x1 - x2;
	float dy = y1 - y2;

	float d = sqrtf(dx*dx+dy*dy);

	if (d < r1 + r2) std::cout << "!!!!!!!!colidiu pouuurrrrrra!!!!!!!!" << std::endl;

}

//testa a colisao de quadrados entre todos os objetos <form>
void collision(mlFormat *self) {

	mlFormat *head = self->getHead();

	for (self = head;self;self = self->getNext()) {

		if (self->getColidState() == FORMAT_COLIDOFF) continue;

		float
			x1 = self->getX(),
			y1 = self->getY(),
			w1 = self->getWidth(),
			h1 = self->getHeight();

		for (mlFormat *selfver = head;selfver;selfver = selfver->getNext()) {

			if (selfver == self) continue;

			float
				x2 = selfver->getX(),
				y2 = selfver->getY(),
				w2 = selfver->getWidth(),
				h2 = selfver->getHeight();

			if
				(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) {
				*self->getColid() = true;
			}
			else
			{
				*self->getColid() = false;
			}
		}
	}
}

#endif 

