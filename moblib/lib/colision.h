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

#include "position.h"

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
		MOB_POSITION trail;
		MOB_FORM form;
		int direction = 0;

		COLID() {}

		COLID(MOB_POSITION* position, MOB_DIMENSION* dimension) {
			form.dimension = dimension;
			form.position = position;
			trail.x = position->x;
			trail.y = position->y;
		}
	};
}

// necessario de usar após realizar um teste de colizão para atualizar o sistema de colizao
// se usar mob_run() com colizão, a colizao ja se auto atualiza
void mob_reload_collision(MOB_COLLISION::COLID* self) {
	self->trail.x = self->form.position->x; self->trail.y = self->form.position->y;
}

// colisao avancada, sem gosth
bool mob_collision(MOB_COLLISION::COLID* self, MOB_FORM* other_object, int obj_in_out) {
	bool colid = false;
	

	if (obj_in_out == MOB_COLLISION::INTERNAL) {
		colid = false;
		if (self->form.position->x <= other_object->position->x - 1) {
			self->form.position->x = other_object->position->x - 1;
			colid = true;
		}
		if (self->form.position->y <= other_object->position->y - 1) {
			self->form.position->y = other_object->position->y - 1;
			colid = true;
		}
		if (self->form.position->x + self->form.dimension->width >= other_object->position->x + other_object->dimension->width + 1) {
			self->form.position->x = other_object->position->x + (other_object->dimension->width - self->form.dimension->width) + 1;
			colid = true;
		}
		if (self->form.position->y + self->form.dimension->height >= other_object->position->y + other_object->dimension->height + 1) {
			self->form.position->y = other_object->position->y + (other_object->dimension->height - self->form.dimension->height) + 1;
			colid = true;
		}

	}

	else if (obj_in_out == MOB_COLLISION::EXTERNAL) {
		colid = true;

		bool ghost_side[4] = { false, false, false, false };
		if (self->trail.y + self->form.dimension->height <= other_object->position->y) { ghost_side[0] = true; }
		if (self->trail.x >= other_object->position->x + other_object->dimension->width) { ghost_side[1] = true; }
		if (self->trail.y >= other_object->position->y + other_object->dimension->height ) { ghost_side[2] = true; }
		if (self->trail.x + self->form.dimension->width <= other_object->position->x ) { ghost_side[3] = true; }

		bool side[4] = { false, false, false, false };
		if (self->form.position->y + self->form.dimension->height <= other_object->position->y) { side[0] = true; }
		if (self->form.position->x >= other_object->position->x + other_object->dimension->width) { side[1] = true; }
		if (self->form.position->y >= other_object->position->y + other_object->dimension->height) { side[2] = true; }
		if (self->form.position->x + self->form.dimension->width <= other_object->position->x) { side[3] = true; }

		bool allside = side[0] + side[1] + side[2] + side[3];

		if      (ghost_side[0] && // cima
			((side[2] && !side[3] && !side[1]) || // colizao em eixos
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) || // colizao em intercessoes
				!allside)) // colizao interna
			self->form.position->y = other_object->position->y - self->form.dimension->height - 1; // reajuste da posição do objeto

		else if (ghost_side[1] && // frente
			((side[3] && !side[2] && !side[0]) || 
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside)) self->form.position->x = other_object->position->x + other_object->dimension->width + 1;

		else if (ghost_side[2] && // baixo 
			((side[0] && !side[3] && !side[1]) || 
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) ||
				!allside)) self->form.position->y = other_object->position->y + other_object->dimension->height + 1;

		else if (ghost_side[3] && // atras
			((side[1] && !side[2] && !side[0]) || 
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside)) self->form.position->x = other_object->position->x - self->form.dimension->width - 1;

		else colid = false; // se nada ocorrer nao houve colizao
	}
	return colid;
}

// colisao avancada, sem gosth. Usando entrada de dados manual
bool mob_collision(MOB_COLLISION::COLID* self, float other_object_x, float other_object_y, float other_object_width, float other_object_height, int obj_in_out) {
	bool colid = false;


	if (obj_in_out == MOB_COLLISION::INTERNAL) {
		colid = false;
		if (self->form.position->x <= other_object_x - 1) {
			self->form.position->x = other_object_x - 1;
			colid = true;
		}
		if (self->form.position->y <= other_object_y - 1) {
			self->form.position->y = other_object_y - 1;
			colid = true;
		}
		if (self->form.position->x + self->form.dimension->width >= other_object_x + other_object_width + 1) {
			self->form.position->x = other_object_x + (other_object_width - self->form.dimension->width) + 1;
			colid = true;
		}
		if (self->form.position->y + self->form.dimension->height >= other_object_y + other_object_height + 1) {
			self->form.position->y = other_object_y + (other_object_height - self->form.dimension->height) + 1;
			colid = true;
		}

	}

	else if (obj_in_out == MOB_COLLISION::EXTERNAL) {
		colid = true;

		bool ghost_side[4] = { false, false, false, false };
		if (self->trail.y + self->form.dimension->height <= other_object_y) { ghost_side[0] = true; }
		if (self->trail.x >= other_object_x + other_object_width) { ghost_side[1] = true; }
		if (self->trail.y >= other_object_y + other_object_height) { ghost_side[2] = true; }
		if (self->trail.x + self->form.dimension->width <= other_object_x) { ghost_side[3] = true; }

		bool side[4] = { false, false, false, false };
		if (self->form.position->y + self->form.dimension->height <= other_object_y) { side[0] = true; }
		if (self->form.position->x >= other_object_x + other_object_width) { side[1] = true; }
		if (self->form.position->y >= other_object_y + other_object_height) { side[2] = true; }
		if (self->form.position->x + self->form.dimension->width <= other_object_x) { side[3] = true; }

		bool allside = side[0] + side[1] + side[2] + side[3];

		if (ghost_side[0] && // cima
			((side[2] && !side[3] && !side[1]) || // colizao em eixos
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) || // colizao em intercessoes
				!allside)) // colizao interna
			self->form.position->y = other_object_y - self->form.dimension->height - 1; // reajuste da posição do objeto

		else if (ghost_side[1] && // frente
			((side[3] && !side[2] && !side[0]) ||
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside)) 
			self->form.position->x = other_object_x + other_object_width + 1;

		else if (ghost_side[2] && // baixo 
			((side[0] && !side[3] && !side[1]) ||
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) ||
				!allside))
			self->form.position->y = other_object_y + other_object_height + 1;

		else if (ghost_side[3] && // atras
			((side[1] && !side[2] && !side[0]) ||
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside)) 
			self->form.position->x = other_object_x - self->form.dimension->width - 1;

		else colid = false; // se nada ocorrer nao houve colizao
	}
	return colid;
}

// colisao avancada, sem gosth. Usando entrada de dados manual
bool mob_collision_mirror(MOB_COLLISION::COLID* self, float other_object_x, float other_object_y, float other_object_width, float other_object_height, MOB_COLLISION::COLID* mirror, int obj_in_out) {
	bool colid = false;


	if (obj_in_out == MOB_COLLISION::INTERNAL) {
		colid = false;
		if (self->form.position->x <= other_object_x - 1) {
			mirror->form.position->x = other_object_x - 1;
			colid = true;
		}
		if (self->form.position->y <= other_object_y - 1) {
			mirror->form.position->y = other_object_y - 1;
			colid = true;
		}
		if (self->form.position->x + self->form.dimension->width >= other_object_x + other_object_width + 1) {
			mirror->form.position->x = other_object_x + (other_object_width - self->form.dimension->width) + 1;
			colid = true;
		}
		if (self->form.position->y + self->form.dimension->height >= other_object_y + other_object_height + 1) {
			mirror->form.position->y = other_object_y + (other_object_height - self->form.dimension->height) + 1;
			colid = true;
		}

	}

	else if (obj_in_out == MOB_COLLISION::EXTERNAL) {
		colid = true;

		bool ghost_side[4] = { false, false, false, false };
		if (self->trail.y + self->form.dimension->height <= other_object_y) { ghost_side[0] = true; }
		if (self->trail.x >= other_object_x + other_object_width) { ghost_side[1] = true; }
		if (self->trail.y >= other_object_y + other_object_height) { ghost_side[2] = true; }
		if (self->trail.x + self->form.dimension->width <= other_object_x) { ghost_side[3] = true; }

		bool side[4] = { false, false, false, false };
		if (self->form.position->y + self->form.dimension->height <= other_object_y) { side[0] = true; }
		if (self->form.position->x >= other_object_x + other_object_width) { side[1] = true; }
		if (self->form.position->y >= other_object_y + other_object_height) { side[2] = true; }
		if (self->form.position->x + self->form.dimension->width <= other_object_x) { side[3] = true; }

		bool allside = side[0] + side[1] + side[2] + side[3];

		if (ghost_side[0] && // cima
			((side[2] && !side[3] && !side[1]) || // colizao em eixos
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) || // colizao em intercessoes
				!allside)) // colizao interna
			mirror->form.position->y = other_object_y - self->form.dimension->height - 1; // reajuste da posição do objeto

		else if (ghost_side[1] && // frente
			((side[3] && !side[2] && !side[0]) ||
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside))
			mirror->form.position->x = other_object_x + other_object_width + 1;

		else if (ghost_side[2] && // baixo 
			((side[0] && !side[3] && !side[1]) ||
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) ||
				!allside))
			mirror->form.position->y = other_object_y + other_object_height + 1;

		else if (ghost_side[3] && // atras
			((side[1] && !side[2] && !side[0]) ||
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside))
			mirror->form.position->x = other_object_x - self->form.dimension->width - 1;

		else colid = false; // se nada ocorrer nao houve colizao
	}
	return colid;
}

// colisao avancada espelhada, sem gosth
bool mob_collision_mirror(MOB_COLLISION::COLID* self, MOB_FORM* other_object, MOB_COLLISION::COLID *mirror, int obj_in_out) {
	bool colid = false;


	if (obj_in_out == MOB_COLLISION::INTERNAL) {
		colid = false;
		if (self->form.position->x <= other_object->position->x - 1) {
			mirror->form.position->x = other_object->position->x - 1;
			colid = true;
		}
		if (self->form.position->y <= other_object->position->y - 1) {
			mirror->form.position->y = other_object->position->y - 1;
			colid = true;
		}
		if (self->form.position->x + self->form.dimension->width >= other_object->position->x + other_object->dimension->width + 1) {
			mirror->form.position->x = other_object->position->x + (other_object->dimension->width - self->form.dimension->width) + 1;
			colid = true;
		}
		if (self->form.position->y + self->form.dimension->height >= other_object->position->y + other_object->dimension->height + 1) {
			mirror->form.position->y = other_object->position->y + (other_object->dimension->height - self->form.dimension->height) + 1;
			colid = true;
		}

	}

	else if (obj_in_out == MOB_COLLISION::EXTERNAL) {
		colid = true;

		bool ghost_side[4] = { false, false, false, false };
		if (self->trail.y + self->form.dimension->height <= other_object->position->y) { ghost_side[0] = true; }
		if (self->trail.x >= other_object->position->x + other_object->dimension->width) { ghost_side[1] = true; }
		if (self->trail.y >= other_object->position->y + other_object->dimension->height) { ghost_side[2] = true; }
		if (self->trail.x + self->form.dimension->width <= other_object->position->x) { ghost_side[3] = true; }

		bool side[4] = { false, false, false, false };
		if (self->form.position->y + self->form.dimension->height <= other_object->position->y) { side[0] = true; }
		if (self->form.position->x >= other_object->position->x + other_object->dimension->width) { side[1] = true; }
		if (self->form.position->y >= other_object->position->y + other_object->dimension->height) { side[2] = true; }
		if (self->form.position->x + self->form.dimension->width <= other_object->position->x) { side[3] = true; }

		bool allside = side[0] + side[1] + side[2] + side[3];

		if (ghost_side[0] && // cima
			((side[2] && !side[3] && !side[1]) || // colizao em eixos
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) || // colizao em intercessoes
				!allside)) // colizao interna
			mirror->form.position->y = other_object->position->y - self->form.dimension->height - 1; // reajuste da posição do objeto

		else if (ghost_side[1] && // frente
			((side[3] && !side[2] && !side[0]) ||
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside))
			mirror->form.position->x = other_object->position->x + other_object->dimension->width + 1;

		else if (ghost_side[2] && // baixo 
			((side[0] && !side[3] && !side[1]) ||
				(!ghost_side[1] && !ghost_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) ||
				!allside))
			mirror->form.position->y = other_object->position->y + other_object->dimension->height + 1;

		else if (ghost_side[3] && // atras
			((side[1] && !side[2] && !side[0]) ||
				(!ghost_side[0] && !ghost_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
				!allside))
			mirror->form.position->x = other_object->position->x - self->form.dimension->width - 1;

		else colid = false; // se nada ocorrer nao houve colizao
	}
	return colid;
}

//colisao avançada, sem gost, com suporte a uma lista encadeada de colisoes
bool mob_collision(MOB_COLLISION::COLID* self, MOB_FORM_CHAIN* list, int obj_in_out) {
	bool colided = false;
	for (MOB_FORM_CHAIN* ptr = list; ptr; ptr = ptr->next) {
		if (mob_collision(self, &list->form, obj_in_out)) colided = true;
	}
	return colided;
}

int mob_position_side(MOB_COLLISION::COLID* self, MOB_FORM* other_object) {
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
	if (!(self->form.position->y + self->form.dimension->height >= other_object->position->y)) { code += 1; }
	if (!(self->form.position->x <= other_object->position->x + other_object->dimension->width)) { code += 10; }
	if (!(self->form.position->y <= other_object->position->y + other_object->dimension->height)) { code += 100; }
	if (!(self->form.position->x + self->form.dimension->width >= other_object->position->x)) { code += 1000; }

	self->direction = code;
	return code;
}

// colisao simples
bool mob_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

// colisao simples
bool mob_collision(MOB_FORM *self1, MOB_FORM *self2) {
	return(self1->position->x < self2->position->x + self2->dimension->width && self1->position->x + self1->dimension->width > self2->position->x &&
		self1->position->y < self2->position->y + self2->dimension->height && self1->position->y + self1->dimension->height > self2->position->y);
}

// colisao simples
bool mob_collision(MOB_FORM *self1, int x2, int y2, int w2, int h2) {
	return(self1->position->x < x2 + w2 && self1->position->x + self1->dimension->width > x2 &&
		self1->position->y < y2 + h2 && self1->position->y + self1->dimension->height > y2);
}

// retorna se dis quadrilateros se sobrepoem
#define colid_out(x1, y1, w1, h1, x2, y2, w2, h2) (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)

// retorna se um quadrilatero especifico(ou parte do mesmo) saiu de outro quadrilatero
#define colid_in(x1, y1, w1, h1, x2, y2, w2, h2) !(x1 > x2 && x1 + w1 < x2 + w2 && y1 > y2 && y1 + w1 < y2 + w2)

// colisao especifica para os eixos, com colisao interna
#define colid_in_axis(a1, l1, a2, l2) !(a1 > a2 && a1 + l1 < a2 + l2)

// colisao especifica para os eixos, com colisao externa
#define colid_out_axis(a1, l1, a2, l2) !(a1 < a2 + l2 && a1 + l1 > a2)

#endif
