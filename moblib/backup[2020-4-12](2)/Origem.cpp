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
	
	mlObject map;
	map.initMovimentInstance(100, 100);
	map.initSheet(32, 32, 18, 18);
	map.initFormat();
	
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
			
			mlRun(pers.movK);

			switch (pers.movK->dirMiddle) {
			case mlKEY_W:
				if (pers.movK->activeUP) {
					pers_anim = 0;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 37;
				}
				break;
			case mlKEY_A:
				if (pers.movK->activeLEFT) {
					pers_anim = 2;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 13;
				}
				break;
			case mlKEY_S:
				if (pers.movK->activeDOWN) {
					pers_anim = 3;
					mlAnim(pers.getAnim(pers_anim));
					pers_anim_pos = pers.getAnim(pers_anim)->index;
				}
				else {
					pers_anim_pos = 1;
				}
				break;
			case mlKEY_D:
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
		

		cout << pers.getAnim(0)->index << '-' << pers.getAnim(1)->index << '-' << pers.getAnim(2)->index << '-' << pers.getAnim(3)->index << '-' << endl;

		// desenhos na tela
		al_draw_bitmap_region(personagens,
			pers.sheet->posX(pers_anim_pos), pers.sheet->posY(pers_anim_pos),
			pers.sheet->getWidth(), pers.sheet->getHeight(),
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
