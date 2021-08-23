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
// variaveis de imagem
ALLEGRO_BITMAP* personagens;
ALLEGRO_BITMAP* tilemap;

// variaveis globais
constexpr int DISPLAY_X = 1080;
constexpr int DISPLAY_Y = 720;
bool parar = false;


// funcao principal
int main(int argc, char **argv) {
	// criando objeto
	mlObject pers;
	pers.initMovimentKeys(100, 100, 2);
	pers.initSheet(576, 576, 12, 8);
	pers.initFormat();
	pers.initAnimationInstance(3, mlANIM_L,20);
	pers.initAnimation(4);
	pers.addAnimation(0);
	pers.addAnimation(12);
	pers.addAnimation(24);
	pers.addAnimation(36);
	// criando variaveis do objeto
	int pers_anim_pos = 0;
	int pers_anim = 0;
	
	mlMovimentAuto mapm(-100, -100);
	mlSheet maps(1024, 1024, 32, 32);
	mlMapping map(&maps,pers.movK,20,20,0,0,DISPLAY_X,DISPLAY_Y);
	mlAnimationInstance mapai(12, mlANIM_F,2);
	mlAnimation mapa(&mapai,0);

	cout << mapa.index;

	mlDirection(&mapm, 600, 600, 1);

	for (int i = 0;i < map.width();i++) {
		for (int e = 0;e < map.width();e+=2) {
			map.addkey(e, i, 162);
		}
	}


	for (int i = 0;i < map.width();i+=3) {
		for (int e = 0;e < map.width();e++) {
			map.addkey(e, i, &mapa.index);
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
	tilemap = al_load_bitmap("chao2-0.png");

	// registrando suporte a eventos
	al_register_event_source(fila, al_get_keyboard_event_source());
	al_register_event_source(fila, al_get_display_event_source(tela));
	al_register_event_source(fila, al_get_timer_event_source(timer));

	// iniciando timer
	al_start_timer(timer);

	// loop principal
	while (!parar) {

		// esperar eventos
		al_wait_for_event(fila, &ev);

		// processar a entrada de eventos
		switch (ev.type) {

		case ALLEGRO_EVENT_DISPLAY_CLOSE:

			parar = true;
			break;

		case ALLEGRO_EVENT_KEY_DOWN:

			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				parar = true;
				break;

			case ALLEGRO_KEY_W:
				pers.movK->activeUP = true;
				break;
			case ALLEGRO_KEY_S:
				pers.movK->activeDOWN = true;
				break;
			case ALLEGRO_KEY_A:
				pers.movK->activeLEFT = true;
				break;
			case ALLEGRO_KEY_D:
				pers.movK->activeRIGHT = true;
				break;
			}
		
			break;

		case ALLEGRO_EVENT_KEY_UP:
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
				pers.movK->activeUP = false;
				break;
			case ALLEGRO_KEY_S:
				pers.movK->activeDOWN = false;
				break;
			case ALLEGRO_KEY_A:
				pers.movK->activeLEFT = false;
				break;
			case ALLEGRO_KEY_D:
				pers.movK->activeRIGHT = false;
				break;
			}
			
		}

		// execussao dentro da faixa de FPS determinada
		if (ev.type == ALLEGRO_EVENT_TIMER && al_event_queue_is_empty(fila)) {
			
			mlRun(pers.movK,false);
			mlRun(&mapm);
			mlAnim(&mapa);

			switch (pers.movK->dirMiddle) {
			case mlUP:
				if (pers.movK->activeUP) {
					pers_anim = 0;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 37;
				}
				break;
			case mlLEFT:
				if (pers.movK->activeLEFT) {
					pers_anim = 2;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 13;
				}
				break;
			case mlDOWN:
				if (pers.movK->activeDOWN) {
					pers_anim = 3;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 1;
				}
				break;
			case mlRIGHT:
				if (pers.movK->activeRIGHT) {
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
		// execussao livre

		for (int i = 0;i < map.width();i++) {
			for (int e = 0;e < map.height();e++) {
				if (map.overdraw(i, e))continue;
				for (int l = 0; l < map.keyLayer(i, e); l++) {
					
					al_draw_bitmap_region(tilemap, map.keyX(i, e, l), map.keyY(i, e, l), map.keyWidth(), map.keyHeight(), map.X(i, e), map.Y(i, e), NULL);
				}
			}
		}


		al_draw_rectangle(100, 100, 400, 400, red, 1);

		// desenhos na tela
		al_draw_bitmap_region(personagens,
			pers.sheet->posX(pers_anim_pos), pers.sheet->posY(pers_anim_pos),
			pers.sheet->width(), pers.sheet->height(),
			pers.movK->x, pers.movK->y, NULL);

		// atualiza a tela
		al_flip_display();
		al_clear_to_color(black);

	}

	// destroi objetos allegro
	al_destroy_display(tela);
	al_destroy_event_queue(fila);
	al_destroy_timer(timer);
	al_destroy_font(fonte16);

	return 0;
}
