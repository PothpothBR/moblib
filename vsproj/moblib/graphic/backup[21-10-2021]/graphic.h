#ifndef GRH_H
#define GRH_H

// arquivos de cabecalho allegro
#include <allegro5/allegro.h> // principla
#include <allegro5/allegro_color.h> // tratamento de cor
#include <allegro5/allegro_image.h> // bitmaps
#include <allegro5/allegro_font.h> // textos
#include <allegro5/allegro_ttf.h> // arquivos de texto ttf
#include <allegro5/allegro_primitives.h> // desenhos primitivos
#include <allegro5/allegro_native_dialog.h> // caixas de dialogo

#define errorlog(text) al_show_native_message_box(screen,"",text,"","OK",ALLEGRO_MESSAGEBOX_ERROR)

class _graphic {

public:
	// variaveis de dados
	const int screen_x = 1080, screen_y = 720;
	int _mouse_x = -1, _mouse_y = -1;
	const float fps = 0.016;
	bool flipsys = true;
	char lastchar = ' ';
	bool keyb_p = false;

	// conteiners allegro...
	// ...para o display
	ALLEGRO_DISPLAY* screen = nullptr;
	// ...para imagens
	ALLEGRO_BITMAP* home_bmp = nullptr;
	ALLEGRO_BITMAP* sprite1 = nullptr;

	// ...para fontes
	ALLEGRO_FONT* text = nullptr;

	// ...especificos para entrada de eventos
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE* queue = nullptr;
	ALLEGRO_EVENT mouse_ev;
	ALLEGRO_EVENT_QUEUE* mouse_queue = nullptr;
	// ...controle de execussao
	ALLEGRO_TIMER* timer = nullptr;

	_graphic() {

		// inicia a biblioteca e seus componentes
		if(!al_init())                     errorlog(" Erro ao iniciar a interface grafica!");
		if(!al_init_native_dialog_addon()) errorlog(" Erro ao iniciar dialogo nativo!");
		if(!al_init_font_addon())          errorlog(" Erro ao iniciar fontes!");
		if(!al_init_image_addon())         errorlog(" Erro ao iniciar imagens!");
		if(!al_init_ttf_addon())           errorlog(" Erro ao iniciar tipagem de fonte!");
		if(!al_init_primitives_addon())    errorlog(" Erro ao iniciar formas primitivas!");
		// inicia o suporte aos perifericos
		if(!al_install_keyboard())         errorlog(" Erro ao iniciar suporte ao teclado!");
		if(!al_install_mouse())            errorlog(" Erro ao iniciar suporte ao mouse!");

		// cria a tela
		screen = al_create_display(screen_x, screen_y);
		if(!screen)                        errorlog(" Erro ao criar a tela!");

		// cria o timer
		timer = al_create_timer(fps);
		if (!timer)                        errorlog(" Erro ao criar temporizador!");

		//cria as filas de eventos
		queue = al_create_event_queue();
		mouse_queue = al_create_event_queue();
		if (!queue)                        errorlog(" Erro ao criar eventos!");
		if (!mouse_queue)                  errorlog(" Erro ao criar eventos de mouse!");

		// adiciona leitura a entrada de eventos dos perifericos
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_display_event_source(screen));
		al_register_event_source(queue, al_get_timer_event_source(timer));
		//entrada especifica para o mouse
		al_register_event_source(mouse_queue, al_get_mouse_event_source());

		// importa imagens
		home_bmp = al_load_bitmap("C:/Users/bruno/Desktop/gatito.png");
		sprite1 = al_load_bitmap("grama-x128.png");

		// importa fontes
		text = al_load_ttf_font("C:/Users/bruno/Google Drive/backups/graphic/lastest/arial.ttf", 16, ALLEGRO_ALIGN_LEFT);
		// inicia o temporizador
		al_start_timer(timer);
	}

	// rotinas graficas vem aki
	bool flip() {

		// atualiza o display
		al_flip_display();
		al_clear_to_color(al_map_rgb(42, 46, 48));

		return flipsys;
	}

	// rotinas logicas aki, imbutido rotinas de eventos
	bool timed() {

		//aguarda entrada de eventos
		al_wait_for_event(queue, &ev);

		// processa os eventos
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			keyb_p = true;
			
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				flipsys = false;
			}

			convert_key();

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			keyb_p = false;

			convert_key();
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			flipsys = false;
		}

		// processa os eventos de mouse
		while (!al_is_event_queue_empty(mouse_queue)) {
			al_get_next_event(mouse_queue, &mouse_ev);

			if (mouse_ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				_mouse_x = mouse_ev.mouse.x;
				_mouse_y = mouse_ev.mouse.y;
			}
			if (mouse_ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
				_mouse_x = mouse_ev.mouse.x;
				_mouse_y = mouse_ev.mouse.y;
			}

		}

		// retorna a execussao controlada
		return (al_is_event_queue_empty(queue) && ev.type == ALLEGRO_EVENT_TIMER);
	}

	// retorna a pos x do mouse
	int mouse_x() {
		return _mouse_x;
	}
	// retorna a posicao y do mouse
	int mouse_y() {
		return _mouse_y;
	}

	char keyboard_input() {
		return lastchar;
	}

	bool keyboard_press() {
		return keyb_p;
	}

	~_graphic() {

		// finaliza os recursos para encerrar o programa
		al_destroy_display(screen);
		al_destroy_bitmap(home_bmp);

	}

	void convert_key() {
		switch (ev.keyboard.keycode) {
		case ALLEGRO_KEY_0:
			lastchar = '0';
			break;
		case ALLEGRO_KEY_1:
			lastchar = '1';
			break;         
		case ALLEGRO_KEY_2:
			lastchar = '2';
			break;
		case ALLEGRO_KEY_3:
			lastchar = '3';
			break;
		case ALLEGRO_KEY_4:
			lastchar = '4';
			break;
		case ALLEGRO_KEY_5:
			lastchar = '5';
			break;
		case ALLEGRO_KEY_6:
			lastchar = '6';
			break;
		case ALLEGRO_KEY_7:
			lastchar = '7';
			break;
		case ALLEGRO_KEY_8:
			lastchar = '8';
			break;
		case ALLEGRO_KEY_9:
			lastchar = '9';
			break;
		case ALLEGRO_KEY_A:
			lastchar = 'a';
			break;
		case ALLEGRO_KEY_B:
			lastchar = 'b';
			break;
		case ALLEGRO_KEY_C:
			lastchar = 'c';
			break;
		case ALLEGRO_KEY_D:
			lastchar = 'd';
			break;
		case ALLEGRO_KEY_E:
			lastchar = 'e';
			break;
		case ALLEGRO_KEY_F:
			lastchar = 'f';
			break;
		case ALLEGRO_KEY_G:
			lastchar = 'g';
			break;
		case ALLEGRO_KEY_H:
			lastchar = 'h';
			break;
		case ALLEGRO_KEY_I:
			lastchar = 'i';
			break;
		case ALLEGRO_KEY_J:
			lastchar = 'j';
			break;
		case ALLEGRO_KEY_K:
			lastchar = 'k';
			break;
		case ALLEGRO_KEY_L:
			lastchar = 'l';
			break;
		case ALLEGRO_KEY_M:
			lastchar = 'm';
			break;
		case ALLEGRO_KEY_N:
			lastchar = 'n';
			break;
		case ALLEGRO_KEY_O:
			lastchar = 'o';
			break;
		case ALLEGRO_KEY_P:
			lastchar = 'p';
			break;
		case ALLEGRO_KEY_Q:
			lastchar = 'q';
			break;
		case ALLEGRO_KEY_R:
			lastchar = 'r';
			break;
		case ALLEGRO_KEY_S:
			lastchar = 's';
			break;
		case ALLEGRO_KEY_T:
			lastchar = 't';
			break;
		case ALLEGRO_KEY_U:
			lastchar = 'u';
			break;
		case ALLEGRO_KEY_V:
			lastchar = 'v';
			break;
		case ALLEGRO_KEY_W:
			lastchar = 'w';
			break;
		case ALLEGRO_KEY_X:
			lastchar = 'x';
			break;
		case ALLEGRO_KEY_Y:
			lastchar = 'y';
			break;
		case ALLEGRO_KEY_Z:
			lastchar = 'z';
			break;
		case ALLEGRO_KEY_SPACE:
			lastchar = ' ';
			break;
		case ALLEGRO_KEY_ENTER:
			lastchar = '\0';
			break;
		case ALLEGRO_KEY_BACKSPACE:
			lastchar = '\b';
			break;
		
		}
	}

}graphic;

#endif
