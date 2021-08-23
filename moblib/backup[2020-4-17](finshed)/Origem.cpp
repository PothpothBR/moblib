// arquivos allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "cores.h"

// arquivos moblib
#include "moblib/moblib.h"

// variaveis allegro
ALLEGRO_DISPLAY* tela;
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT ev;
ALLEGRO_EVENT_QUEUE* fila;
ALLEGRO_FONT* fonte16;
ALLEGRO_MOUSE_STATE stateMouse;
// variaveis de imagem
ALLEGRO_BITMAP* personagens;
ALLEGRO_BITMAP* tilemap;
ALLEGRO_BITMAP *seta;
// variaveis globais
constexpr int DISPLAY_X = 1080;
constexpr int DISPLAY_Y = 720;
bool parar = false;


// funcao principal
int main(int argc, char **argv) {

	mlMovimentInstance buttonExit(1030, 0);
	mlFormat objbuttonExit(&buttonExit, 50, 50);

	mlMovimentInstance buttonUp(524, 644);
	mlMovimentInstance buttonDown(524, 678);
	mlMovimentInstance buttonLeft(490, 678);
	mlMovimentInstance buttonRight(558, 678);

	mlFormat objButtonUp(&buttonUp, 32, 32);
	mlFormat objButtonDown(&buttonDown, 32, 32);
	mlFormat objButtonLeft(&buttonLeft, 32, 32);
	mlFormat objButtonRight(&buttonRight, 32, 32);

	mlMovimentInstance mouse(-10, -10);
	mlFormat objmouse(&mouse, 1, 1);

	// criando objeto
	mlObject<mlMovimentKeys> pers;
	pers.initMoviment(100, 100, 2);
	pers.initSheet(576, 576, 12, 8);
	pers.initFormat();
	pers.initAnimationInstance(3, mlANIM_L,20);
	pers.initAnimation(4);
	pers.setAnimation(0);
	pers.setAnimation(12);
	pers.setAnimation(24);
	pers.setAnimation(36);
	// criando variaveis do objeto
	int pers_anim_pos = 0;
	int pers_anim = 0;
	
	mlObject<> map;

	map.initSheet(1024, 1024, 32, 32);
	map.initMoviment(0, 0);
	map.initMapping(34, 23, 0, 0, DISPLAY_X, DISPLAY_Y);
	map.initAnimationInstance(4, mlANIM_F, 21);
	map.initAnimation(1);
	map.setAnimation(352);


	for (int i = 0;i < map.mappg->map->height();i++) {
		for (int e = 0;e < map.mappg->map->width();e++) {
			for (int j = 0;j < 1;j++) {
				map.mappg->map->set(e, i, &map.getAnim(0)->index);
			}
		}
	}
	
	for (int i = 0;i < map.mappg->map->height()*map.mappg->map->width();i++) {
		for (int l = 0;l < map.mappg->map->sizel(i);l++) {
		}
	}
	
	// iniciando componentes
	al_init();
	al_init_native_dialog_addon();
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	// dando suporte a entradas
	al_install_keyboard();
	al_install_mouse();

	// criando objetos allegro
	timer = al_create_timer(0.016);
	fila = al_create_event_queue();
	fonte16 = al_load_ttf_font("serifa-light.ttf", 16, NULL);
	tela = al_create_display(DISPLAY_X, DISPLAY_Y);
	personagens = al_load_bitmap("pers.png");
	tilemap = al_load_bitmap("anima1-0.png");
	seta = al_load_bitmap("seta100x66.png");
	// registrando suporte a eventos
	al_register_event_source(fila, al_get_keyboard_event_source());
	al_register_event_source(fila, al_get_display_event_source(tela));
	al_register_event_source(fila, al_get_timer_event_source(timer));
	al_register_event_source(fila, al_get_mouse_event_source());
	// iniciando timer
	al_start_timer(timer);

	// loop principal
	while (!parar) {

		// esperar eventos
		al_wait_for_event(fila, &ev);
		
		// processar a entrada de eventos
		switch (ev.type) {

		case ALLEGRO_EVENT_MOUSE_AXES:
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			al_get_mouse_state(&stateMouse);
			if (stateMouse.buttons & 1) {
				mouse.x = stateMouse.x;
				mouse.y = stateMouse.y;
				mlIsolatedCollision(&objmouse, &objbuttonExit);
				if (mouse.colid) return 1;

				if (mlIsolatedCollision(&objmouse, &objButtonUp)) { pers.mov->activeUP = true; }
				else if (mlIsolatedCollision(&objmouse, &objButtonDown)) { pers.mov->activeDOWN = true; }
				if (mlIsolatedCollision(&objmouse, &objButtonLeft)) { pers.mov->activeLEFT = true; }
				else if (mlIsolatedCollision(&objmouse, &objButtonRight)) { pers.mov->activeRIGHT = true; }
			}
			break;

		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

			pers.mov->activeUP = false;
			pers.mov->activeDOWN = false;
			pers.mov->activeLEFT = false;
			pers.mov->activeRIGHT = false;
			break;

		case ALLEGRO_EVENT_TOUCH_BEGIN:
			mouse.x = ev.touch.x;
			mouse.y = ev.touch.y;
			mlIsolatedCollision(&objmouse, &objbuttonExit);
			if (mouse.colid) return 0;

			if (mlIsolatedCollision(&objmouse, &objButtonUp)) { pers.mov->activeUP = true; }
			else if (mlIsolatedCollision(&objmouse, &objButtonDown)) { pers.mov->activeDOWN = true; }
			if (mlIsolatedCollision(&objmouse, &objButtonLeft)) { pers.mov->activeLEFT = true; }
			else if (mlIsolatedCollision(&objmouse, &objButtonRight)) { pers.mov->activeRIGHT = true; }
			break;

		case ALLEGRO_EVENT_TOUCH_END:
			pers.mov->activeUP = false;
			pers.mov->activeDOWN = false;
			pers.mov->activeLEFT = false;
			pers.mov->activeRIGHT = false;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:

			parar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				parar = true;
				break;

			case ALLEGRO_KEY_W:
				pers.mov->activeUP = true;
				break;
			case ALLEGRO_KEY_S:
				pers.mov->activeDOWN = true;
				break;
			case ALLEGRO_KEY_A:
				pers.mov->activeLEFT = true;
				break;
			case ALLEGRO_KEY_D:
				pers.mov->activeRIGHT = true;
				break;
			}
		
			break;

		case ALLEGRO_EVENT_KEY_UP:
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				pers.mov->activeUP = false;
				break;
			case ALLEGRO_KEY_S:
				pers.mov->activeDOWN = false;
				break;
			case ALLEGRO_KEY_A:
				pers.mov->activeLEFT = false;
				break;
			case ALLEGRO_KEY_D:
				pers.mov->activeRIGHT = false;
				break;
			}
			
		}

		// execussao dentro da faixa de FPS determinada
		if (ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(fila)) {
			
			mlRun(pers.mov,false);
			mlAnim(map.getAnim(0));

			switch (pers.mov->dirMiddle) {
			case mlUP:
				if (pers.mov->activeUP) {
					pers_anim = 0;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 37;
				}
				break;
			case mlLEFT:
				if (pers.mov->activeLEFT) {
					pers_anim = 2;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 13;
				}
				break;
			case mlDOWN:
				if (pers.mov->activeDOWN) {
					pers_anim = 3;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 1;
				}
				break;
			case mlRIGHT:
				if (pers.mov->activeRIGHT) {
					pers_anim = 1;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 25;
				}
				break;
			}

		}
		else {
			al_flush_event_queue(fila);
		}
		// execussao livre

		for (int e = 0;e < map.mappg->map->height();e++) {
			for (int i = 0;i < map.mappg->map->width();i++) {
				if (map.mappg->overdraw(i, e))continue;
				for (int l = 0; l < map.mappg->map->sizel(i, e); l++) {
					al_draw_bitmap_region(tilemap, map.mappg->tileX(i, e, l), map.mappg->tileY(i, e, l), map.mappg->tileWidth(), map.mappg->tileHeight(), map.mappg->X(i, e), map.mappg->Y(i, e), NULL);
				}

			}
		}

		al_draw_filled_rectangle(buttonExit.x, buttonExit.y, buttonExit.x + objbuttonExit.getWidth(), buttonExit.y + objbuttonExit.getHeight(), smokyblack);

		al_draw_rectangle(buttonExit.x, buttonExit.y, buttonExit.x + objbuttonExit.getWidth(), buttonExit.y + objbuttonExit.getHeight(), darkscarlet, 5);

		al_draw_rectangle(buttonUp.x, buttonUp.y, buttonUp.x + objButtonUp.getWidth(), buttonUp.y + objButtonUp.getHeight(), black, 1);
		al_draw_rectangle(buttonDown.x, buttonDown.y, buttonDown.x + objButtonDown.getWidth(), buttonDown.y + objButtonDown.getHeight(), black, 1);
		al_draw_rectangle(buttonLeft.x, buttonLeft.y, buttonLeft.x + objButtonLeft.getWidth(), buttonLeft.y + objButtonLeft.getHeight(), black, 1);
		al_draw_rectangle(buttonRight.x, buttonRight.y, buttonRight.x + objButtonRight.getWidth(), buttonRight.y + objButtonRight.getHeight(), black, 1);

		sint sizeModf = 1;

		al_draw_scaled_bitmap(seta, 0, 0, 100, 66,
			1080 / 2 - 100 * sizeModf / 2, 720 - 66 * sizeModf - 10, 100 * sizeModf, 66 * sizeModf, 1);



		// desenhos na tela
		al_draw_bitmap_region(personagens,
			pers.sheet->posX(pers_anim_pos), pers.sheet->posY(pers_anim_pos),
			pers.sheet->width(), pers.sheet->height(),
			pers.mov->x, pers.mov->y, NULL);

		// atualiza a tela
		al_flip_display();
		al_clear_to_color(cinzafundo);

	}

	// destroi objetos allegro
	al_destroy_display(tela);
	al_destroy_event_queue(fila);
	al_destroy_timer(timer);
	al_destroy_font(fonte16);

	return 0;
}