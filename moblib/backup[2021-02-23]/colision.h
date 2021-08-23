#ifndef COLISION_H
#define COLISION_H

#include <cstdlib>

namespace COLLISION {

	const int IN = 0;  // <object::obj_colid> objeto esta dentro de outro;
	const int OUT = 1; // <object::obj_colid> objeto esta fora de outro;

	class COLID {
	public:

		int width = 0, height = 0;
		float *x = 0, *y = 0;
		int obj_pers_lado = 0;
		

		int dir_mov = 0;// tem de ser implementado ainda...


		// pode haver um erro com o obj_pers_lado, nao sendo nessesario ser ponteiro
		COLID(float *position_x, float *position_y, int width, int height) {
			x = position_x, y = position_y;
			this->width = width, this->height = height;
		}

	};


	// colisao avancada, sem gosth
	bool collision(COLLISION::COLID* self, COLLISION::COLID* otr_obj, int obj_in_out) {

		bool colid = false;

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
			/*
			// para debbuging

			if (self->obj_pers_lado == 0) { al_draw_circle(*self->x + (self->width / 2), *self->y + self->height + (self->height * 0.1), 8, blue, 2); }
			if (self->obj_pers_lado == 1) { al_draw_circle(*self->x - (self->width * 0.1), *self->y + (self->height / 2), 8, blue, 2); }
			if (self->obj_pers_lado == 2) { al_draw_circle(*self->x + (self->width / 2), *self->y - (self->height * 0.1), 8, blue, 2); }
			if (self->obj_pers_lado == 3) { al_draw_circle(*self->x + self->width + (self->width * 0.1), *self->y + (self->height / 2), 8, blue, 2); }

			al_draw_filled_circle(*self->x + (self->width / 2), *self->y + self->height + (self->height * 0.1), 6, red);
			al_draw_filled_circle(*self->x - (self->width * 0.1), *self->y + (self->height / 2), 6, red);
			al_draw_filled_circle(*self->x + (self->width / 2), *self->y - (self->height * 0.1), 6, red);
			al_draw_filled_circle(*self->x + self->width + (self->height * 0.1), *self->y + (self->height / 2), 6, red);

			if (lado[0]) { al_draw_filled_circle(*self->x + (self->width / 2), *self->y + self->height + (self->height * 0.1), 6, green); }
			if (lado[1]) { al_draw_filled_circle(*self->x - (self->width * 0.1), *self->y + (self->height / 2), 6, green); }
			if (lado[2]) { al_draw_filled_circle(*self->x + (self->width / 2), *self->y - (self->height * 0.1), 6, green); }
			if (lado[3]) { al_draw_filled_circle(*self->x + self->width + (self->height * 0.1), *self->y + (self->height / 2), 6, green); }

			al_draw_filled_rectangle(*self->x, *self->y, *self->x + self->width, *self->y + self->height, al_map_rgba(0, 0, 0, 90));
			*/
			if ((self->obj_pers_lado == 0) && (!lado[2] && (lado[0] && lado[1] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				*self->y = *otr_obj->y - self->height;
				//al_draw_circle(*self->x + (self->width / 2), *self->y + self->height + 12, 12, black, 2);
				colid = true;
			}
			if ((self->obj_pers_lado== 1) && (!lado[3] && (lado[0] && lado[1] && lado[2]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				*self->x = *otr_obj->x + otr_obj->width;
				//al_draw_circle(*self->x - 12, *self->y + (self->height / 2), 12, black, 2);
				colid = true;
			}
			if ((self->obj_pers_lado == 2) && (!lado[0] && (lado[1] && lado[2] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				*self->y = *otr_obj->y + otr_obj->height;
				//al_draw_circle(*self->x + (self->width / 2), *self->y - 12, 12, black, 2);
				colid = true;
			}
			if ((self->obj_pers_lado == 3) && (!lado[1] && (lado[0] && lado[2] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
				//al_draw_circle(*self->x + self->width + 12, *self->y + (self->height / 2), 12, black, 2);
				*self->x = *otr_obj->x - self->width;
				colid = true;

			}
			if (!colid) {
				if (!lado[0]) { self->obj_pers_lado = 0; }
				else if (!lado[1]) { self->obj_pers_lado = 1; }
				else if (!lado[2]) { self->obj_pers_lado = 2; }
				else if (!lado[3]) { self->obj_pers_lado = 3; }
			}
		}

		//al_flip_display();
		return colid;
	}

	// colisao simples
	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
		return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
	}

	// colisao simples
	bool collision(COLID *self1, COLID *self2) {
		return(*self1->x < *self2->x + self2->width && *self1->x + self1->width > *self2->x && *self1->y < *self2->y + self2->height && *self1->y + self1->height > *self2->y);
	}

	// colisao simples
	bool collision(COLID *self1, int x2, int y2, int w2, int h2) {
		return(*self1->x < x2 + w2 && *self1->x + self1->width > x2 && *self1->y < y2 + h2 && *self1->y + self1->height > y2);
	}

	// retorna se dis quadrilateros se sobreporam
	#define colid_out(x1, y1, w1, h1, x2, y2, w2, h2) (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)
	// retorna se um quadrilatero especifico(ou parte do mesmo) saiu de outro quadrilatero
	#define colid_in(x1, y1, w1, h1, x2, y2, w2, h2) !(x1 > x2 && x1 + w1 < x2 + w2 && y1 > y2 && y1 + w1 < y2 + w2)
	// colisao especifica para os eixos
	#define colid_in_axis(a1, l1, a2, l2) !(a1 > a2 && a1 + l1 < a2 + l2)
	#define colid_out_axis(a1, l1, a2, l2) !(a1 < a2 + l2 && a1 + l1 > a2)

}

#endif
