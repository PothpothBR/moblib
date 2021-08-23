#ifndef COLISION_H
#define COLISION_H

#include <cstdlib>

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

namespace MOB_COLLISION {

	const int IN = 0;  // <object::obj_colid> objeto esta dentro de outro;
	const int OUT = 1; // <object::obj_colid> objeto esta fora de outro;

	constexpr sint UP = 0;
	constexpr sint LEFT = 1;
	constexpr sint DOWN = 2;
	constexpr sint RIGHT = 3;

	constexpr sint UP_LEFT = 4;
	constexpr sint UP_RIGHT = 5;
	constexpr sint DOWN_LEFT = 6;
	constexpr sint DOWN_RIGHT = 7;

	class COLID {
	public:

		int width = 0, height = 0;
		float* x = 0, * y = 0;
		float ghost_x = 0, ghost_y = 0;

		int moviment_direction = 0;// tem de ser implementado ainda...


		// pode haver um erro com o obj_pers_lado, nao sendo nessesario ser ponteiro
		COLID(float* position_x, float* position_y, int width, int height) {
			x = position_x, y = position_y;
			ghost_x = *position_x, ghost_y = *position_y;
			this->width = width, this->height = height;
		}

		// apos todas as colisoes recaregue o sistema de colisoes, para usar novamente na proxima execussao
		void reload() { ghost_x = *x; ghost_y = *y; }
	};

}



// colisao avancada, sem gosth
bool mob_collision(MOB_COLLISION::COLID* self, MOB_COLLISION::COLID* other_object, int obj_in_out, bool deb = false) {

	bool colid = false;

	if (obj_in_out == MOB_COLLISION::IN) {

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

	else if (obj_in_out == MOB_COLLISION::OUT) {

		/*

			9       1       3
			  #############
			  #############
			8 ############# 2
			  #############
			  #############
			12      4       6

		*/

		/*
					2

			  #############
			  #############
		  1   #############   3
			  #############
			  #############

					0
		*/

		/*int obj_pers_lado = 0;

		// verifica todos os lados para descobrir qual esta, o que esta é inserido em obj_pers_lado
		if (!(self->ghost_y + self->height >= *other_object->y + 1)) { obj_pers_lado = 0; }
		else if (!(self->ghost_x <= *other_object->x + other_object->width - 1)) { obj_pers_lado = 1; }
		else if (!(self->ghost_y <= *other_object->y + other_object->height - 1)) { obj_pers_lado = 2; }
		else if (!(self->ghost_x + self->width >= *other_object->x + 1)) { obj_pers_lado = 3; }
		*/

		bool ghost_lado[4] = { true, true, true, true };

		if (self->ghost_y + self->height >= *other_object->y + 1) { ghost_lado[0] = false; }
		if (self->ghost_x <= *other_object->x + other_object->width - 1) { ghost_lado[1] = false; }
		if (self->ghost_y <= *other_object->y + other_object->height - 1) { ghost_lado[2] = false; }
		if (self->ghost_x + self->width >= *other_object->x + 1) { ghost_lado[3] = false; }

		bool lado[4] = { true, true, true, true };

		// verifica todos os lados para descobrir qual esta, o que esta é o true
		if (*self->y + self->height >= *other_object->y + 1) { lado[0] = false; }
		if (*self->x <= *other_object->x + other_object->width - 1) { lado[1] = false; }
		if (*self->y <= *other_object->y + other_object->height - 1) { lado[2] = false; }
		if (*self->x + self->width >= *other_object->x + 1) { lado[3] = false; }
		/*
		// para debbuging
		if (deb) {

								  al_draw_filled_circle(self->ghost_x + (self->width / 2), self->ghost_y + self->height + (self->height * 0.1), 6, red);
								  al_draw_filled_circle(self->ghost_x - (self->width * 0.1), self->ghost_y + (self->height / 2), 6, red);
								  al_draw_filled_circle(self->ghost_x + (self->width / 2), self->ghost_y - (self->height * 0.1), 6, red);
								  al_draw_filled_circle(self->ghost_x + self->width + (self->width * 0.1), self->ghost_y + (self->height / 2), 6, red);

			if (!ghost_lado[0]) { al_draw_filled_circle(self->ghost_x + (self->width / 2), self->ghost_y + self->height + (self->height * 0.1), 6, blue); }
			if (!ghost_lado[1]) { al_draw_filled_circle(self->ghost_x - (self->width * 0.1), self->ghost_y + (self->height / 2), 6, blue); }
			if (!ghost_lado[2]) { al_draw_filled_circle(self->ghost_x + (self->width / 2), self->ghost_y - (self->height * 0.1), 6, blue); }
			if (!ghost_lado[3]) { al_draw_filled_circle(self->ghost_x + self->width + (self->width * 0.1), self->ghost_y + (self->height / 2), 6, blue); }

							al_draw_filled_circle(*self->x + (self->width / 2), *self->y + self->height + (self->height * 0.1), 6, red);
							al_draw_filled_circle(*self->x - (self->width * 0.1), *self->y + (self->height / 2), 6, red);
							al_draw_filled_circle(*self->x + (self->width / 2), *self->y - (self->height * 0.1), 6, red);
							al_draw_filled_circle(*self->x + self->width + (self->width * 0.1), *self->y + (self->height / 2), 6, red);

			if (!lado[0]) { al_draw_filled_circle(*self->x + (self->width / 2), *self->y + self->height + (self->height * 0.1), 6, green); }
			if (!lado[1]) { al_draw_filled_circle(*self->x - (self->width * 0.1), *self->y + (self->height / 2), 6, green); }
			if (!lado[2]) { al_draw_filled_circle(*self->x + (self->width / 2), *self->y - (self->height * 0.1), 6, green); }
			if (!lado[3]) { al_draw_filled_circle(*self->x + self->width + (self->width * 0.1), *self->y + (self->height / 2), 6, green); }

			al_draw_filled_rectangle(*self->x, *self->y, *self->x + self->width, *self->y + self->height, al_map_rgba(0, 0, 0, 80));
		}
		// se for o lado 0 e somente o lado 2 ou nao for nenhum lado
		if      ((ghost_lado[0] && (lado[2] && !lado[0] && !lado[1] && !lado[3]) || (!lado[0] && !lado[1] && !lado[2] && !lado[3])) || 
			((ghost_lado[0] && !ghost_lado[1] && !ghost_lado[2] && !ghost_lado[3]) && ((lado[2] && lado[1]) || (lado[2] && lado[3])))
			) {
			*self->y = *other_object->y - self->height;
			if (deb)al_draw_circle(*self->x + (self->width / 2), *self->y + self->height + 12, 12, black, 2);
			colid = true;
		}
		else if ((ghost_lado[1] && (lado[3] && !lado[0] && !lado[1] && !lado[2]) || (!lado[0] && !lado[1] && !lado[2] && !lado[3])) ||
			((ghost_lado[1] && !ghost_lado[0] && !ghost_lado[2] && !ghost_lado[3]) && ((lado[3] && lado[0]) || (lado[3] && lado[2])))) {
			*self->x = *other_object->x + other_object->width;
			if (deb)al_draw_circle(*self->x - 12, *self->y + (self->height / 2), 12, black, 2);
			colid = true;
		}
		else if ((ghost_lado[2] && (lado[0] && !lado[1] && !lado[2] && !lado[3]) || (!lado[0] && !lado[1] && !lado[2] && !lado[3])) ||
			((ghost_lado[0] && !ghost_lado[1] && !ghost_lado[2] && !ghost_lado[3]) && ((lado[0] && lado[1]) || (lado[0] && lado[2])))) {
			*self->y = *other_object->y + other_object->height;
			if (deb)al_draw_circle(*self->x + (self->width / 2), *self->y - 12, 12, black, 2);
			colid = true;
		}
		else if ((ghost_lado[3] && (lado[1]  && !lado[0] && !lado[2] && !lado[3]) || (!lado[0] && !lado[1] && !lado[2] && !lado[3])) ||
			((ghost_lado[0] && !ghost_lado[1] && !ghost_lado[2] && !ghost_lado[3]) && ((lado[1] && lado[2]) || (lado[1] && lado[3])))) {
			*self->x = *other_object->x - self->width;
			if (deb)al_draw_circle(*self->x + self->width + 12, *self->y + (self->height / 2), 12, black, 2);
			colid = true;
		}

		if (deb) {
			al_draw_rectangle(self->ghost_x, self->ghost_y, self->ghost_x + self->width, self->ghost_y + self->height, black, 4);
			al_draw_rectangle(*self->x, *self->y, *self->x + self->width, *self->y + self->height, red, 1);
		}
		
	}

	if (deb) al_flip_display();*/
	return colid;
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
