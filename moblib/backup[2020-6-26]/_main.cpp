#include "headers/_graphic.h"

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
				  2
			#############
			#############
		  1 ############# 3
			#############
			#############
			      0
		*/

		bool lado[4] = { false, false,false,false };

		// verifica todos os lados para descobrir qual esta, o que esta é o false
		if (*self->y + self->height >= *otr_obj->y +1  ) { lado[0] = true;  }
		if (*self->x <= *otr_obj->x + otr_obj->width -1 ) { lado[1] = true;  }
		if (*self->y <= *otr_obj->y + otr_obj->height -1 ) { lado[2] = true;  }
		if (*self->x + self->width >= *otr_obj->x +1 ) { lado[3] = true;  }

		if (self->obj_pers_lado[i_pers_lado] == 0) { al_draw_circle(*self->x + 25, *self->y + self->height + 5, 8, black,2); }
		if (self->obj_pers_lado[i_pers_lado] == 1) { al_draw_circle(*self->x - 5, *self->y + 25, 8,  black,2); }
		if (self->obj_pers_lado[i_pers_lado] == 2) { al_draw_circle(*self->x + 25, *self->y - 5, 8,  black,2); }
		if (self->obj_pers_lado[i_pers_lado] == 3) { al_draw_circle(*self->x + self->width + 5, *self->y + 25, 8, black,2); }

		al_draw_filled_circle(*self->x + 25, *self->y + self->height + 5, 6, red);
		al_draw_filled_circle(*self->x - 5, *self->y + 25, 6, red);
		al_draw_filled_circle(*self->x + 25, *self->y - 5, 6, red);
		al_draw_filled_circle(*self->x + self->width + 5, *self->y + 25, 6, red);

		if (lado[0]){ al_draw_filled_circle(*self->x + 25, *self->y + self->height + 5, 6, green); }
		if (lado[1]){ al_draw_filled_circle(*self->x - 5, *self->y + 25, 6, green); }
		if (lado[2]){ al_draw_filled_circle(*self->x + 25, *self->y - 5, 6, green); }
		if (lado[3]){ al_draw_filled_circle(*self->x + self->width + 5, *self->y + 25, 6, green); }

		al_draw_filled_rectangle(*self->x, *self->y, *self->x + self->width, *self->y + self->height, al_map_rgba(0,0,0,90) );
		
		/*COLLISION::COLID bigRect(new float(0), new float(0), 0, 0);

		int pointx1, pointy1, pointx2, pointy2;

		if (lado[0]) {
			pointy1 = *self->y;
			switch (self->obj_pers_lado[i_pers_lado]) {
			case 0:

				break;
			}
		}
		else if (lado[1]) {
			pointx1 = *self->x + self->width;

		}
		else if (lado[2]) {
			pointy1 = *self->y + self->height;

		}
		else if (lado[3]) {
			pointx1 = *self->x;

		}*/
		
		if ((self->obj_pers_lado[i_pers_lado] == 0) && (!lado[2] && (lado[0] && lado[1] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3]) ) {
			*self->y = *otr_obj->y - self->height;
			al_draw_circle(*self->x + 25, *self->y + self->height + 12, 12, black, 2);
			colid = true;
		}
		if ((self->obj_pers_lado[i_pers_lado] == 1) && (!lado[3] && (lado[0] && lado[1] && lado[2]) || lado[0] && lado[1] && lado[2] && lado[3])) {
			*self->x = *otr_obj->x + otr_obj->width;
			al_draw_circle(*self->x - 12, *self->y + 25, 12, black, 2);
			colid = true;
		}
		if ((self->obj_pers_lado[i_pers_lado] == 2) && (!lado[0] && (lado[1] && lado[2] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
			*self->y = *otr_obj->y + otr_obj->height;
			al_draw_circle(*self->x + 25, *self->y - 12, 12, black, 2);
			colid = true;
		}
		if ((self->obj_pers_lado[i_pers_lado] == 3) && (!lado[1] && (lado[0] && lado[2] && lado[3]) || lado[0] && lado[1] && lado[2] && lado[3])) {
			al_draw_circle(*self->x + self->width + 12, *self->y + 25, 12, black, 2);
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
	al_flip_display();
	al_rest(1);
	return colid;

	

}

int main() {
	// inicia o timer
	al_start_timer(timer);
	// loop principal
	while (Core.loop()) {
		// execução em FPS
		if (Core.timedExecution()) {
			
			// aguar ate liberar outro evento
			channel->wait();

			for (int i = 0;i < map->mapping->map->width; i++ ) {
				for (int e = 0; e < map->mapping->map->height; e++) {
					if (!overdraw(map->mapping, map->moviment->pos, map->sheet, i, e) && cell(map->mapping->map, i, e, 1) != 0) {
						// testa a colisao com os tiles do jogo
						// se colidir para o loop

						
					}
				}
			} 
			// movimenta o mapa
			MOVIMENT::run(map->moviment);
			// simula o movimento do personagem (ja que é o mapa que se move)
			MOVIMENT::run(player->moviment);
			// muda a animaçao do personagem
			switchPlayerAnimation(player, pswitch);
			
			MOVIMENT::run(player1->moviment);
			collision(player1->format, test, COLLISION::OUT);
			

		}
		// manipula a fila de threads
		manipQueue(channel);
	}
	
	
	return 0;
}
