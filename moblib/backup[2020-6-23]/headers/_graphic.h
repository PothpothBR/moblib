#ifndef _GRAPHIC_H
#define _GRAPHIC_H

#include "_routines.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "_colors.h"

// cria variavel de fim de jogo
bool endGame = false;

// cria classe da tela
ALLEGRO_DISPLAY* screen = nullptr;

// cria as filas de evento e classes de eventos e timer
ALLEGRO_EVENT ev;
ALLEGRO_EVENT mouse_ev;
ALLEGRO_EVENT_QUEUE* queue = nullptr;
ALLEGRO_EVENT_QUEUE* mouse_queue = nullptr;
ALLEGRO_EVENT_QUEUE* timer_queue = nullptr;
ALLEGRO_TIMER* timer = nullptr;
ALLEGRO_BITMAP* player_sheet = nullptr;
ALLEGRO_BITMAP* map_sheet = nullptr;
ALLEGRO_BITMAP* map_sheet_anim = nullptr;

// instancia evento
void events();

// nucleo do programa
class _GraphicCore {
public:

	// junta as 3 classes <_frontEnd | _backEnd | _tempCache> iniciando-as
	_GraphicCore() {

		// inicia a biblioteca allegro
		al_init();
		// inicia os modulos
		al_init_image_addon();
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();

		// cria a tela
		screen = al_create_display(1080, 720);

		// instala suporte a dispositivos
		al_install_keyboard();
		al_install_mouse();

		// cria filas e timer
		queue = al_create_event_queue();
		mouse_queue = al_create_event_queue();
		timer = al_create_timer(FPS); // aredondado 0.0166666~

		// registra eventos
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_timer_event_source(timer));
		al_register_event_source(mouse_queue, al_get_mouse_event_source());
		al_register_event_source(queue, al_get_display_event_source(screen));

		// inicia as classes
		player_sheet = al_load_bitmap("pers.png");
		map_sheet = al_load_bitmap("map-sheet.png");
		map_sheet_anim = al_load_bitmap("terra-anim.png");
		
	}

	// retorna se a execucao sera timed e coleta os eventos
	bool timedExecution() {
		events();
		return (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue));
	}

	// atualiza a tela e define se o programa continuara
	bool loop() {
		al_flip_display();
		al_clear_to_color(lightskyblue);

		for (int i = 0;i < map->mapping->map->width;i++) {
			for (int e = 0; e < map->mapping->map->height;e++) {
				if (!overdraw(map->mapping, map->moviment->pos, map->sheet,i,e)) {
					
					switch (cell(map->mapping->map, i, e, 0)) {
					case 1:
						al_draw_bitmap_region(map_sheet, map->sheet->cellX[2], map->sheet->cellY[2],map->sheet->cellWidth, map->sheet->cellHeight,  mapX(map->moviment->pos, map->sheet, i, e), mapY(map->moviment->pos, map->sheet, i, e), NULL);
						break;

					case 2:
						al_draw_bitmap_region(map_sheet, map->sheet->cellX[0], map->sheet->cellY[0], map->sheet->cellWidth, map->sheet->cellHeight, mapX(map->moviment->pos, map->sheet, i, e), mapY(map->moviment->pos, map->sheet, i, e), NULL);
						break;
					case 3:
						al_draw_bitmap_region(map_sheet, map->sheet->cellX[3], map->sheet->cellY[3], map->sheet->cellWidth, map->sheet->cellHeight, mapX(map->moviment->pos, map->sheet, i, e), mapY(map->moviment->pos, map->sheet, i, e), NULL);
						break;
				}
				}
			}
		}
		// execucao livre

		THREAD *get = channel->head[channel->getChanelById(22)];
		for (int i = 0;i < channel->size[channel->getChanelById(22)];i++) {
			shoot_atack *tmp = (shoot_atack*)get->obj;
			// aqui vai a execusao referente ao thread <tmp><id = 32>
			al_draw_filled_rectangle(tmp->bullet->pos->x, tmp->bullet->pos->y, tmp->bullet->pos->x + tmp->bulletform->width, tmp->bullet->pos->y + tmp->bulletform->height, blue);
			//al_draw_rectangle(tmp->bullet->pos->x, tmp->bullet->pos->y, tmp->bullet->pos->x + tmp->bulletform->width, tmp->bullet->pos->y + tmp->bulletform->height, red, 1);
			// ----------------------------------------
			get = get->next;
		}


		al_draw_bitmap_region(player_sheet,
			player->sheet->cellX[pswitch->anim_pos],
			player->sheet->cellY[pswitch->anim_pos],
			player->sheet->cellWidth, player->sheet->cellHeight,
			player->moviment->pos->x, player->moviment->pos->y, NULL);

		al_draw_bitmap_region(player_sheet,
			player1->sheet->cellX[p1switch->anim_pos],
			player1->sheet->cellY[p1switch->anim_pos],
			player1->sheet->cellWidth, player1->sheet->cellHeight,
			player1->moviment->pos->x, player1->moviment->pos->y, NULL);
		al_draw_rectangle(
			player1->moviment->pos->x + player1->sheet->cellWidth,
			player1->moviment->pos->y + player1->sheet->cellHeight,
			player1->moviment->pos->x, player1->moviment->pos->y, red, 1);
		return !endGame;
	}

	~_GraphicCore() {
		// destroi filas e timer
		al_destroy_event_queue(queue);
		al_destroy_event_queue(mouse_queue);
		al_destroy_timer(timer);

		// destroi a tela
		al_destroy_display(screen);

		// destroi as classes
		al_destroy_bitmap(player_sheet);
		al_destroy_bitmap(map_sheet);
		al_destroy_bitmap(map_sheet_anim);
	}

}Core;

void events() {
	//espera por eventos de mouse e os outros separados
	al_wait_for_event(queue, &ev);
	al_get_next_event(mouse_queue, &mouse_ev);
	if (mouse_ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
		al_get_next_event(mouse_queue, &mouse_ev);
	}
	//procesa eventos de mouse
	switch (mouse_ev.type) {
	case ALLEGRO_EVENT_MOUSE_AXES:
		mouse->MOVING = true;
		mouse->pos->x = mouse_ev.mouse.x;
		mouse->pos->y = mouse_ev.mouse.y;
		break;

	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		mouse->LEFT = true;
		mouse->pos->x = mouse_ev.mouse.x;
		mouse->pos->y = mouse_ev.mouse.y;
		break;

	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		mouse->LEFT = false;
		break;
	default:
		mouse->MOVING = false;
	}

	// processar as outras entradas de eventos
	switch (ev.type) {

	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		endGame = true;
		break;

	case ALLEGRO_EVENT_KEY_DOWN:

		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			endGame = true;
			break;
		case ALLEGRO_KEY_W:
			map->moviment->DOWN = true;
			player->moviment->UP = true;
			break;
		case ALLEGRO_KEY_S:
			map->moviment->UP = true;
			player->moviment->DOWN = true;
			break;
		case ALLEGRO_KEY_A:
			map->moviment->RIGHT = true;
			player->moviment->LEFT = true;
			break;
		case ALLEGRO_KEY_D:
			map->moviment->LEFT = true;
			player->moviment->RIGHT = true;
			break;
		case ALLEGRO_KEY_UP:
			player1->moviment->UP = true;
			break;
		case ALLEGRO_KEY_DOWN:
			player1->moviment->DOWN = true;
			break;
		case ALLEGRO_KEY_LEFT:
			player1->moviment->LEFT = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			player1->moviment->RIGHT = true;
			break;
		}
		break;

	case ALLEGRO_EVENT_KEY_UP:
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			map->moviment->DOWN = false;
			player->moviment->UP = false;
			break;
		case ALLEGRO_KEY_S:
			map->moviment->UP = false;
			player->moviment->DOWN = false;
			break;
		case ALLEGRO_KEY_A:
			map->moviment->RIGHT = false;
			player->moviment->LEFT = false;
			break;
		case ALLEGRO_KEY_D:
			map->moviment->LEFT = false;
			player->moviment->RIGHT = false;
			break;
		case ALLEGRO_KEY_UP:
			player1->moviment->UP = false;
			break;
		case ALLEGRO_KEY_DOWN:
			player1->moviment->DOWN = false;
			break;
		case ALLEGRO_KEY_LEFT:
			player1->moviment->LEFT = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			player1->moviment->RIGHT = false;
			break;
		}
		break;
	}
}

#endif