#include "headers/_graphic.h"

ALLEGRO_COLOR cr;

int main() {
	

	cr = al_map_rgb(0, 0, 0);

	al_start_timer(timer);
	// loop principal
	while (Core.loop()) {
		// execução em FPS
		if (Core.timedExecution()) {
			
			channel->wait();// aguar ate liberar outro evento

			if (MOVIMENT::collision(_mouse,player1->moviment->pos->x,player1->moviment->pos->y,player1->sheet->cellWidth,player1->sheet->cellHeight) && mouse->LEFT) {// player atacando player1

				attack(player, player1->moviment->pos, player1->sheet, channel);
			}
			
			bool colid = false;
			MOVIMENT::INSTANCE coltest;
			MOVIMENT::before_run(map->moviment, &coltest);// pega a posicao do mapa apos o movimento
			for (int i = 0;i < map->mapping->map->width && !colid;i++ ) {// nda
				
				for (int e = 0; e < map->mapping->map->height && !colid;e++) {
					
					if (!overdraw(map->mapping, map->moviment->pos, map->sheet, i, e) && cell(map->mapping->map, i, e, 1) != 0) {
						
						if (MOVIMENT::collision(player->format, mapX(&coltest, map->sheet, i, e), mapY(&coltest, map->sheet, i, e), 32, 32)) {
							cr = al_map_rgb(255, 0, 0);
							colid = true;
						}
						else cr = al_map_rgb(0, 255, 0);

						al_draw_rectangle(*player->format->x,*player->format->y,
							*player->format->x + player->format->width, *player->format->y + player->format->height, cr,1 );
						al_draw_rectangle(mapX(map->moviment->pos, map->sheet, i, e), mapY(map->moviment->pos, map->sheet, i, e),
							mapX(map->moviment->pos, map->sheet, i, e) + 32, mapY(map->moviment->pos, map->sheet, i, e) + 32, cr, 1);
					}
				}
			}

			/*pre teste de gravidade*/

			/*----------------------*/
			if (!colid) {
				MOVIMENT::run(map->moviment, &coltest);// se colidiu nao adiciona o movimento
			}
			MOVIMENT::run(player1->moviment, player1->format, player->format);
			MOVIMENT::run(player->moviment, player->format, player1->format);

			switchPlayerAnimation(player, pswitch);
			switchPlayerAnimation(player1, p1switch);

			


			
		}
		manipQueue(channel);
	}
	
	
	return 0;
}
