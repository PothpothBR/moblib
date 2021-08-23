#ifndef COLISION_H
#define COLISION_H

#include <cstdlib>

namespace COLLISION {

	const int IN = 0;  // <object::obj_colid> objeto esta dentro de outro;
	const int OUT = 1; // <object::obj_colid> objeto esta fora de outro; se a velocidade do objeto for maior que o tamanho do colisor, o objeto "pulara" ele;

	class COLID {
	public:

		int width = 0, height = 0;
		float *x = 0, *y = 0;
		int *obj_pers_lado = nullptr;
		int ID;
		static int IDsize;
		int dir_mov = 0;

		COLID(float *position_x, float *position_y, int width, int height) {
			x = position_x, y = position_y;
			this->width = width, this->height = height;
			ID = IDsize++;
			obj_pers_lado = (int*)realloc(obj_pers_lado, sizeof(int*) * IDsize);
			obj_pers_lado[IDsize - 1] = 0;
		}

	};

	int COLID::IDsize = 0;

	bool collision(COLLISION::COLID* self, COLLISION::COLID* otr_obj, int obj_in_out) { // se colidir encosta os dois objetos e nao trava o movimento

		bool colid = false;
		int i_pers_lado = self->ID;

		if (obj_in_out == COLLISION::IN) {

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

		else if (obj_in_out == COLLISION::OUT) {

			/*

			  9       1       3
				#############
				#############
			  8 ############# 2
				#############
				#############
			  12      4       6

			*/

			bool lado[4] = { false, false,false,false };

			// verifica todos os lados para descobrir qual esta, o que esta é o false
			if (*self->y + self->height >= *otr_obj->y + 1) { lado[0] = true; }
			if (*self->x <= *otr_obj->x + otr_obj->width - 1) { lado[1] = true; }
			if (*self->y <= *otr_obj->y + otr_obj->height - 1) { lado[2] = true; }
			if (*self->x + self->width >= *otr_obj->x + 1) { lado[3] = true; }

			/*if (self->obj_pers_lado[i_pers_lado] == 0) { al_draw_circle(*self->x + 25, *self->y + self->height + 5, 8, black, 2); }
			if (self->obj_pers_lado[i_pers_lado] == 1) { al_draw_circle(*self->x - 5, *self->y + 25, 8, black, 2); }
			if (self->obj_pers_lado[i_pers_lado] == 2) { al_draw_circle(*self->x + 25, *self->y - 5, 8, black, 2); }
			if (self->obj_pers_lado[i_pers_lado] == 3) { al_draw_circle(*self->x + self->width + 5, *self->y + 25, 8, black, 2); }

			al_draw_filled_circle(*self->x + 25, *self->y + self->height + 5, 6, red);
			al_draw_filled_circle(*self->x - 5, *self->y + 25, 6, red);
			al_draw_filled_circle(*self->x + 25, *self->y - 5, 6, red);
			al_draw_filled_circle(*self->x + self->width + 5, *self->y + 25, 6, red);

			if (lado[0]) { al_draw_filled_circle(*self->x + 25, *self->y + self->height + 5, 6, green); }
			if (lado[1]) { al_draw_filled_circle(*self->x - 5, *self->y + 25, 6, green); }
			if (lado[2]) { al_draw_filled_circle(*self->x + 25, *self->y - 5, 6, green); }
			if (lado[3]) { al_draw_filled_circle(*self->x + self->width + 5, *self->y + 25, 6, green); }

			al_draw_filled_rectangle(*self->x, *self->y, *self->x + self->width, *self->y + self->height, al_map_rgba(0, 0, 0, 90));
			*/
			if ((self->obj_pers_lado[i_pers_lado] == 0) && (!lado[2] && (lado[0] && lado[1] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				*self->y = *otr_obj->y - self->height;
				//al_draw_circle(*self->x + 25, *self->y + self->height + 12, 12, black, 2);
				colid = true;
			}
			if ((self->obj_pers_lado[i_pers_lado] == 1) && (!lado[3] && (lado[0] && lado[1] && lado[2]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				*self->x = *otr_obj->x + otr_obj->width;
				//al_draw_circle(*self->x - 12, *self->y + 25, 12, black, 2);
				colid = true;
			}
			if ((self->obj_pers_lado[i_pers_lado] == 2) && (!lado[0] && (lado[1] && lado[2] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				*self->y = *otr_obj->y + otr_obj->height;
				//al_draw_circle(*self->x + 25, *self->y - 12, 12, black, 2);
				colid = true;
			}
			if ((self->obj_pers_lado[i_pers_lado] == 3) && (!lado[1] && (lado[0] && lado[2] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				//al_draw_circle(*self->x + self->width + 12, *self->y + 25, 12, black, 2);
				*self->x = *otr_obj->x - self->width;
				colid = true;

			}
			if (!colid) {
				if (!lado[0]) { self->obj_pers_lado[i_pers_lado] = 0; }
				else if (!lado[1]) { self->obj_pers_lado[i_pers_lado] = 1; }
				else if (!lado[2]) { self->obj_pers_lado[i_pers_lado] = 2; }
				else if (!lado[3]) { self->obj_pers_lado[i_pers_lado] = 3; }
			}
		}

		//al_flip_display();
		//al_rest(1);
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
