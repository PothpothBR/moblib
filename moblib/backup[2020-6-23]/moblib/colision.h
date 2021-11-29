#ifndef COLISION_H
#define COLISION_H

#include <cstdlib>

namespace COLLISION {

	typedef short int sint;
	typedef unsigned short int usint;
	typedef const unsigned short int c_usint;

	const usint IN = 0;  // <object::obj_colid> objeto esta dentro de outro;
	const usint OUT = 1; // <object::obj_colid> objeto esta fora de outro; se a velocidade do objeto for maior que o tamanho do colisor, o objeto "pulara" ele;

	class COLID {
	public:

		usint width = 0, height = 0;
		sint *x = 0, *y = 0;
		usint *obj_pers_lado = nullptr;
		usint ID;
		static usint IDsize;
		usint dir_mov = 0;

		COLID(float *position_x, float *position_y, usint width, usint height) {
			x = position_x, y = position_y;
			this->width = width, this->height = height;
			ID = IDsize++;
			obj_pers_lado = (usint*)realloc(obj_pers_lado, sizeof(usint*) * IDsize);
		}

	};

	usint COLID::IDsize = 0;

	bool collision(COLID* self, COLID* otr_obj, usint obj_in_out) { // se colidir encosta os dois objetos e nao trava o movimento

		bool colid = false;
		usint i_pers_lado = otr_obj->ID;

		if (obj_in_out == IN) {

			if (*self->x <= *otr_obj->x - 1) {
				*self->x = *otr_obj->x - 1;
				colid = true;
			}
			if (*self->y <= *otr_obj->y - 1) {
				*self->y = *otr_obj->y - 1;
				colid = true;
			}
			if (*self->x + self->width >= *otr_obj->x + otr_obj->width + 1) {
				*self->x = *otr_obj->x + (otr_obj->width - self->width) + 1;
				colid = true;
			}
			if (*self->y + self->height >= *otr_obj->y + otr_obj->height + 1) {
				*self->y = *otr_obj->y + (otr_obj->height - self->height) + 1;
				colid = true;
			}

		}
		else if (obj_in_out == OUT) {

			bool lado[4] = { false };

			if (*self->y + self->height >= *otr_obj->y) { lado[0] = true; }
			if (*self->x <= *otr_obj->x + otr_obj->width) { lado[1] = true; }
			if (*self->y <= *otr_obj->y + otr_obj->height) { lado[2] = true; }
			if (*self->x + self->width >= *otr_obj->x) { lado[3] = true; }
			if (!lado[0]) { self->obj_pers_lado[i_pers_lado] = 1; }
			if (!lado[1]) { self->obj_pers_lado[i_pers_lado] = 2; }
			if (!lado[2]) { self->obj_pers_lado[i_pers_lado] = 3; }
			if (!lado[3]) { self->obj_pers_lado[i_pers_lado] = 4; }

			if ((self->obj_pers_lado[i_pers_lado] == 1) && (lado[0] == true)) {
				*self->y = *otr_obj->y - self->height;
				colid = true;
			}
			if ((self->obj_pers_lado[i_pers_lado] == 2) && (lado[1] == true)) {
				*self->x = *otr_obj->x + otr_obj->width;
				colid = true;
			}
			if ((self->obj_pers_lado[i_pers_lado] == 3) && (lado[2] == true)) {
				*self->y = *otr_obj->y + otr_obj->height;
				colid = true;
			}
			if ((self->obj_pers_lado[i_pers_lado] == 4) && (lado[3] == true)) {
				*self->x = *otr_obj->x - self->width;
				colid = true;
			}

			//lado[0] = false, lado[1] = false ,lado[2] = false, lado[3] = false;
		}

		return colid;

	}

	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
		return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
	}

	bool collision(COLID *self1, COLID *self2) {
		return(*self1->x < *self2->x + self2->width && *self1->x + self1->width > *self2->x && *self1->y < *self2->y + self2->height && *self1->y + self1->height > *self2->y);
	}

	bool collision(COLID *self1, int x2, int y2, int w2, int h2) {
		return(*self1->x < x2 + w2 && *self1->x + self1->width > x2 && *self1->y < y2 + h2 && *self1->y + self1->height > y2);
	}
}
#endif
