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

#ifndef COLISION_H
#define COLISION_H

#include <cstdlib>

#include <iostream>
using namespace std;

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

namespace MOB_COLLISION {

	const int INTERNAL = 0;  // <object::obj_colid> objeto esta dentro de outro;
	const int EXTERNAL = 1; // <object::obj_colid> objeto esta fora de outro;

	constexpr sint UP = 1;
	constexpr sint LEFT = 10;
	constexpr sint DOWN = 100;
	constexpr sint RIGHT = 1000;

	constexpr sint UP_LEFT = 11;
	constexpr sint UP_RIGHT = 1001;
	constexpr sint DOWN_LEFT = 101;
	constexpr sint DOWN_RIGHT = 1100;

	class COLID {
	public:

		float width = 0, height = 0;
		float* x = 0, * y = 0;
		float ghost_x = 0, ghost_y = 0;

		int moviment_direction = 0;

		COLID() {}

		// pode haver um erro com o obj_pers_lado, nao sendo nessesario ser ponteiro
		COLID(float* position_x, float* position_y, float width, float height) {
			x = position_x, y = position_y;
			ghost_x = *position_x, ghost_y = *position_y;
			this->width = width, this->height = height;
		}

		// apos todas as colisoes recaregue o sistema de colisoes, para usar novamente na proxima execussao
		void reload() { ghost_x = *x; ghost_y = *y; }
	};

}



// colisao avancada, sem gosth
bool mob_collision(MOB_COLLISION::COLID* self, MOB_COLLISION::COLID* other_object, int obj_in_out) {
	bool colid = false;
	

	if (obj_in_out == MOB_COLLISION::INTERNAL) {
		colid = false;
		if (*self->x <= *other_object->x - 1) {
			*self->x = *other_object->x - 1;
			colid = true;
		}
		if (*self->y <= *other_object->y - 1) {
			*self->y = *other_object->y - 1;
			colid = true;
		}
		if (*self->x + self->width >= *other_object->x + other_object->width + 1) {
			*self->x = *other_object->x + (other_object->width - self->width) + 1;
			colid = true;
		}
		if (*self->y + self->height >= *other_object->y + other_object->height + 1) {
			*self->y = *other_object->y + (other_object->height - self->height) + 1;
			colid = true;
		}

	}

	else if (obj_in_out == MOB_COLLISION::EXTERNAL) {
		colid = true;

		bool ghost_side[4] = { false, false, false, false };
		if (self->ghost_y + self->height <= *other_object->y) { ghost_side[0] = true; }
		if (self->ghost_x >= *other_object->x + other_object->width) { ghost_side[1] = true; }
		if (self->ghost_y >= *other_object->y + other_object->height ) { ghost_side[2] = true; }
		if (self->ghost_x + self->width <= *other_object->x ) { ghost_side[3] = true; }

		bool side[4] = { false, false, false, false };
		if (*self->y + self->height <= *other_object->y) { side[0] = true; }
		if (*self->x >= *other_object->x + other_object->width) { side[1] = true; }
		if (*self->y >= *other_object->y + other_object->height) { side[2] = true; }
		if (*self->x + self->width <= *other_object->x) { side[3] = true; }

		bool allside = side[0] + side[1] + side[2] + side[3];

		if      (ghost_side[0] && // cima
			((side[2] && !side[3] && !side[1]) || // colizao em eixos
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) || // colizao em intercessoes
				!allside)) // colizao interna
			*self->y = *other_object->y - self->height - 1; // reajuste da posição do objeto

		else if (ghost_side[1] && // frente
			((side[3] && !side[2] && !side[0]) || 
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside)) *self->x = *other_object->x + other_object->width + 1;

		else if (ghost_side[2] && // baixo 
			((side[0] && !side[3] && !side[1]) || 
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) ||
				!allside)) *self->y = *other_object->y + other_object->height + 1;

		else if (ghost_side[3] && // atras
			((side[1] && !side[2] && !side[0]) || 
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside)) *self->x = *other_object->x - self->width - 1;

		else colid = false; // se nada ocorrer nao houve colizao
	}
	return colid;
}

int mob_position_side(MOB_COLLISION::COLID* self, MOB_COLLISION::COLID* other_object) {
	     /* devolve um codigo de posicionamento bruto

		 1001       1       11 
			  #############	   
			  #############	   
		 1000 ############# 10 
			  #############	   
			  #############	   
		 1100      100     110
         */
	int code = 0;
	if (!(*self->y + self->height >= *other_object->y)) { code += 1; }
	if (!(*self->x <= *other_object->x + other_object->width)) { code += 10; }
	if (!(*self->y <= *other_object->y + other_object->height)) { code += 100; }
	if (!(*self->x + self->width >= *other_object->x)) { code += 1000; }

	self->moviment_direction = code;
	return code;
}

// colisao simples
bool mob_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

// colisao simples
bool mob_collision(MOB_COLLISION::COLID *self1, MOB_COLLISION::COLID *self2) {
	return(*self1->x < *self2->x + self2->width && *self1->x + self1->width > *self2->x && *self1->y < *self2->y + self2->height && *self1->y + self1->height > *self2->y);
}

// colisao simples
bool mob_collision(MOB_COLLISION::COLID *self1, int x2, int y2, int w2, int h2) {
	return(*self1->x < x2 + w2 && *self1->x + self1->width > x2 && *self1->y < y2 + h2 && *self1->y + self1->height > y2);
}

// retorna se dis quadrilateros se sobreporam
#define colid_out(x1, y1, w1, h1, x2, y2, w2, h2) (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)

// retorna se um quadrilatero especifico(ou parte do mesmo) saiu de outro quadrilatero
#define colid_in(x1, y1, w1, h1, x2, y2, w2, h2) !(x1 > x2 && x1 + w1 < x2 + w2 && y1 > y2 && y1 + w1 < y2 + w2)

// colisao especifica para os eixos, com colisao interna
#define colid_in_axis(a1, l1, a2, l2) !(a1 > a2 && a1 + l1 < a2 + l2)

// colisao especifica para os eixos, com colisao externa
#define colid_out_axis(a1, l1, a2, l2) !(a1 < a2 + l2 && a1 + l1 > a2)

#endif
