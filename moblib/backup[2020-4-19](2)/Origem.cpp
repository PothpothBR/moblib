// arquivos allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "cores.h"

// arquivos moblib
#include "moblib/moblib.h"

//#define MOBILE_DEVICE

// variaveis allegro
ALLEGRO_DISPLAY* tela;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT ev;
ALLEGRO_EVENT mousev;
ALLEGRO_EVENT_QUEUE* fila;
ALLEGRO_EVENT_QUEUE* mousefila;
ALLEGRO_FONT* fonte16;
// variaveis de imagem
ALLEGRO_BITMAP* personagens;
ALLEGRO_BITMAP* tilemap;
// variaveis globais
constexpr int DISPLAY_X = 1080;
constexpr int DISPLAY_Y = 720;
bool parar = false;


// funcao principal
int main(int argc, char **argv) {


#ifdef MOBILE_DEVICE

	mlMovimentInstance buttonExit(1030, 0);
	mlFormat objbuttonExit(&buttonExit, 50, 50);
	mlMovimentInstance buttonUp(524, 512);
	mlMovimentInstance buttonDown(524, 578);
	mlMovimentInstance buttonLeft(490-32, 578);
	mlMovimentInstance buttonRight(558+32, 578);
	mlFormat objButtonUp(&buttonUp, 64, 64);
	mlFormat objButtonDown(&buttonDown, 64, 64);
	mlFormat objButtonLeft(&buttonLeft, 64, 64);
	mlFormat objButtonRight(&buttonRight, 64, 64);

#else
	mlMovimentInstance mouse(-10, -10);
	mlFormat objmouse(&mouse, 1, 1);
#endif
	// criando objeto
	mlObject<mlMovimentKeys> pers(4);
	pers.moviment = initMoviment<mlMovimentKeys>(100, 100, 2);
	pers.sheet = initSheet(576, 576, 12, 8);
	pers.format = initFormat<mlMovimentKeys>(pers.moviment,pers.sheet);
	pers.animInstance = initAnimationInstance(3, mlANIM_F,20);
	pers.animation = initAnimation(&pers.animSize);
	pers.animation[3] = setAnimation(pers.animInstance, 0);
	pers.animation[2] = setAnimation(pers.animInstance, 12);
	pers.animation[1] = setAnimation(pers.animInstance, 24);
	pers.animation[0] = setAnimation(pers.animInstance, 36);
	// criando variaveis do objeto
	int pers_anim_pos = 0;
	int pers_anim = 0;
	
	mlObject<> map(1);

	map.sheet = initSheet(1024, 1024, 32, 32);
	map.moviment = initMoviment<>(0, 0);
	map.mapping = initMapping(34, 23, 0, 0, DISPLAY_X, DISPLAY_Y);
	map.animInstance = initAnimationInstance(5, mlANIM_F, 21);
	map.animation = initAnimation(&pers.animSize);
	map.animation[0] = setAnimation(pers.animInstance, 352);


	for (int i = 0;i < map.mapping->map->height;i++) {
		for (int e = 0;e < map.mapping->map->width;e++) {
			for (int j = 0;j < 1;j++) {
				add(map.mapping->map, e, i, &map.animation[0]->index);
			}
		}
	}
	
	// iniciando componentes
	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
#ifdef MOBILE_DEVICE
	al_install_touch_input();
#else
	// dando suporte a entradas
	al_install_keyboard();
	al_install_mouse();
	mousefila = al_create_event_queue();
#endif
	// criando objetos allegro
	timer = al_create_timer(0.016);
	fila = al_create_event_queue();
	
	fonte16 = al_load_ttf_font("serifa-light.ttf", 16, NULL);
	
	personagens = al_load_bitmap("pers.png");
	tilemap = al_load_bitmap("anima1-0.png");
#ifdef MOBILE_DEVICE
	al_register_event_source(fila, al_get_touch_input_event_source());
#else
	// registrando suporte a eventos
	al_register_event_source(fila, al_get_keyboard_event_source());
	al_register_event_source(fila, al_get_display_event_source(tela));
	al_register_event_source(fila, al_get_timer_event_source(timer));
	al_register_event_source(mousefila, al_get_mouse_event_source());
#endif
	// iniciando timer
	al_start_timer(timer);
	tela = al_create_display(DISPLAY_X, DISPLAY_Y);
	// loop principal
	while (!parar) {

		// esperar eventos
		al_wait_for_event(fila, &ev);
		al_get_next_event(mousefila, &mousev);

		switch (mousev.type) {
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			mouse.x = mousev.mouse.x;
			mouse.y = mousev.mouse.y;
		}

		// processar a entrada de eventos
		switch (ev.type) {

#ifdef MOBILE_DEVICE
		case ALLEGRO_EVENT_TOUCH_BEGIN:
			mouse.x = ev.touch.x;
			mouse.y = ev.touch.y;
			mlIsolatedCollision(&objmouse, &objbuttonExit);
			if (mouse.colid) return 0;

			if (mlIsolatedCollision(&objmouse, &objButtonUp)) { pers.moviment->activeUP = true; }
			else if (mlIsolatedCollision(&objmouse, &objButtonDown)) { pers.moviment->activeDOWN = true; }
			if (mlIsolatedCollision(&objmouse, &objButtonLeft)) { pers.moviment->activeLEFT = true; }
			else if (mlIsolatedCollision(&objmouse, &objButtonRight)) { pers.moviment->activeRIGHT = true; }
			break;

		case ALLEGRO_EVENT_TOUCH_END:
			pers.moviment->activeUP = false;
			pers.moviment->activeDOWN = false;
			pers.moviment->activeLEFT = false;
			pers.moviment->activeRIGHT = false;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:

			parar = true;
			break;
#else
		case ALLEGRO_EVENT_DISPLAY_CLOSE:

			parar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				parar = true;
				break;

			case ALLEGRO_KEY_W:
				pers.moviment->activeUP = true;
				break;
			case ALLEGRO_KEY_S:
				pers.moviment->activeDOWN = true;
				break;
			case ALLEGRO_KEY_A:
				pers.moviment->activeLEFT = true;
				break;
			case ALLEGRO_KEY_D:
				pers.moviment->activeRIGHT = true;
				break;
			}
		
			break;

		case ALLEGRO_EVENT_KEY_UP:
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				pers.moviment->activeUP = false;
				break;
			case ALLEGRO_KEY_S:
				pers.moviment->activeDOWN = false;
				break;
			case ALLEGRO_KEY_A:
				pers.moviment->activeLEFT = false;
				break;
			case ALLEGRO_KEY_D:
				pers.moviment->activeRIGHT = false;
				break;
			}
			break;
#endif
		}

		// execussao dentro da faixa de FPS determinada
		if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(fila)) {
			
			mlRun(pers.moviment,false);
			mlAnim(map.animation[0]);

			switch (pers.moviment->dirMiddle) {
			case mlUP:
				if (pers.moviment->activeUP) {
					pers_anim = 0;
					mlAnim(pers.animation[pers_anim]);
					pers_anim_pos = pers.animation[pers_anim]->index;
				}
				else {
					pers_anim_pos = 37;
				}
				break;
			case mlLEFT:
				if (pers.moviment->activeLEFT) {
					pers_anim = 2;
					mlAnim(pers.animation[pers_anim]);
					pers_anim_pos = pers.animation[pers_anim]->index;
				}
				else {
					pers_anim_pos = 13;
				}
				break;
			case mlDOWN:
				if (pers.moviment->activeDOWN) {
					pers_anim = 3;
					mlAnim(pers.animation[pers_anim]);
					pers_anim_pos = pers.animation[pers_anim]->index;
				}
				else {
					pers_anim_pos = 1;
				}
				break;
			case mlRIGHT:
				if (pers.moviment->activeRIGHT) {
					pers_anim = 1;
					mlAnim(pers.animation[pers_anim]);
					pers_anim_pos = pers.animation[pers_anim]->index;
				}
				else {
					pers_anim_pos = 25;
				}
				break;
			}


		}

		// execussao livre

		for (int e = 0;e < map.mapping->map->height;e++) {
			for (int i = 0;i < map.mapping->map->width;i++) {
				if (overdraw(map.mapping, map.moviment, map.sheet, i, e))continue;
				for (int l = 0; l < cellSize(map.mapping->map,i, e); l++) {
					al_draw_bitmap_region(tilemap, tileX(map.mapping, map.sheet, i, e, l), tileY(map.mapping, map.sheet, i, e, l), map.sheet->cellWidth, map.sheet->cellHeight,
										  mapX(map.moviment, map.sheet, i, e), mapY(map.moviment, map.sheet, i, e), NULL);
				}

			}
		}
#ifdef MOBILE_DEVICE
		al_draw_filled_rectangle(buttonExit.x, buttonExit.y, buttonExit.x + objbuttonExit.width, buttonExit.y + objbuttonExit.height, smokyblack);

		al_draw_rectangle(buttonExit.x, buttonExit.y, buttonExit.x + objbuttonExit.width, buttonExit.y + objbuttonExit.height, darkscarlet, 5);

		al_draw_rectangle(buttonUp.x, buttonUp.y, buttonUp.x + objButtonUp.width, buttonUp.y + objButtonUp.height, black, 1);
		al_draw_rectangle(buttonDown.x, buttonDown.y, buttonDown.x + objButtonDown.width, buttonDown.y + objButtonDown.height, black, 1);
		al_draw_rectangle(buttonLeft.x, buttonLeft.y, buttonLeft.x + objButtonLeft.width, buttonLeft.y + objButtonLeft.height, black, 1);
		al_draw_rectangle(buttonRight.x, buttonRight.y, buttonRight.x + objButtonRight.width, buttonRight.y + objButtonRight.height, black, 1);
#endif

		// desenhos na tela
		al_draw_bitmap_region(personagens,
			pers.sheet->cellX[pers_anim_pos], pers.sheet->cellY[pers_anim_pos],
			pers.sheet->cellWidth, pers.sheet->cellHeight,
			pers.moviment->x, pers.moviment->y, NULL);

		// atualiza a tela
		al_flip_display();
		al_clear_to_color(cinzafundo);

	}

	// destroi objetos allegro
	al_destroy_display(tela);
	al_destroy_event_queue(fila);
	al_destroy_timer(timer);
	al_destroy_font(fonte16);
	al_destroy_bitmap(personagens);
	al_destroy_bitmap(tilemap);

	return 0;
}