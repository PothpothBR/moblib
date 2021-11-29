/*----------------------------------------------------
  |               Programa feito por                 |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  ----------------------------------------------------
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     /  _|             |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/

//  serve para analizar os recursos da biblioteca

#ifndef DEBUGLOG_H
#define DEBUGLOG_H

#define START_ENGINE

#ifdef START_ENGINE


#include <iostream>
// classes para armazenamento de dados------------

constexpr int ___moviment___ = 0;
constexpr int ___sheet___ = 1;
constexpr int ___animation___ = 2;
constexpr int ___mapping___ = 3;
constexpr int ___thread___ = 4;
constexpr int ___collision___ = 5;
constexpr int ___timing___ = 6;

constexpr int __instance__ = 0;
constexpr int __instance_ghost__ = 1;
constexpr int __keyboard__ = 2;
constexpr int __auto__ = 3;
constexpr int __mouse__ = 4;
constexpr int __touch__ = 5;

constexpr int _default_ = 0;
constexpr int _instance_ = 0;
constexpr int _instance_ghost_ = 1;





/*

 ___moviment___ +------------------
				|	__instance__ +---------
				|			     | _default_
				|			     +---------
				|	__instance_ghost__ +---------
				|					   | _default_
				|					   +---------
 				|	__keyboard__ +---------
				|			     | _instance_
				| 		         | _instance_ghost_
				|			     +---------
 				|	__auto__ +---------
				|			 | _instance_
				| 			 | _instance_ghosth_
				|			 +---------
 				|	__mouse__ +---------
				|			  | _instance_
				| 			  | _instance_ghosth_
				|			  +---------
 				|	__touch__ +---------
				|			  | _instance_
				| 			  | _instance_ghosth_
				|			  +---------
				+------------------
 ___sheet___ 
 ___animation___
 ___mapping___
 ___thread___
 ___collision___
 ___timing___

*/

class _MEGADOOR {
public:

	void ***megabuffer[7][6] = { nullptr };

	int *sizes[7][6] = { nullptr };

	_MEGADOOR() {
		
		megabuffer[___moviment___][__instance__] =       (void***)calloc(sizeof(void**), 1);
		megabuffer[___moviment___][__instance_ghost__] = (void***)calloc(sizeof(void**), 1);
		megabuffer[___moviment___][__keyboard__] =       (void***)calloc(sizeof(void**), 2);
		megabuffer[___moviment___][__auto__] =           (void***)calloc(sizeof(void**), 2);
		megabuffer[___moviment___][__mouse__] =          (void***)calloc(sizeof(void**), 2);
		megabuffer[___moviment___][__touch__] =          (void***)calloc(sizeof(void**), 2);

		sizes[___moviment___][__instance__] =       (int*)calloc(sizeof(int), 1);
		sizes[___moviment___][__instance__][_default_] = 0;
		sizes[___moviment___][__instance_ghost__] = (int*)calloc(sizeof(int), 1);
		sizes[___moviment___][__instance_ghost__][_default_] = 0;
		sizes[___moviment___][__keyboard__] =	    (int*)calloc(sizeof(int), 2);
		sizes[___moviment___][__keyboard__][_instance_] = 0;
		sizes[___moviment___][__keyboard__][_instance_ghost_] = 0;
		sizes[___moviment___][__auto__] =		    (int*)calloc(sizeof(int), 2);
		sizes[___moviment___][__auto__][_instance_] = 0;
		sizes[___moviment___][__auto__][_instance_ghost_] = 0;
		sizes[___moviment___][__mouse__] =			(int*)calloc(sizeof(int), 2);
		sizes[___moviment___][__mouse__][_instance_] = 0;
		sizes[___moviment___][__mouse__][_instance_ghost_] = 0;
		sizes[___moviment___][__touch__] =			(int*)calloc(sizeof(int), 2);
		sizes[___moviment___][__touch__][_instance_] = 0;
		sizes[___moviment___][__touch__][_instance_ghost_] = 0;

	}
	
	void _setdoor(int ___flags, int __flags, int _flags , void* door) {

		megabuffer[___flags][__flags][_flags] = (void**)realloc(megabuffer[___flags][__flags][_flags], sizeof(void**) * ++sizes[___flags][__flags][_flags]);
		megabuffer[___flags][__flags][_flags][sizes[___flags][__flags][_flags] - 1] = door;

	}
	
	~_MEGADOOR() {
		
	}
}MEGADOOR;

#define setdoor(___flags,  __flags,  _flags, door) MEGADOOR._setdoor(___flags,  __flags,  _flags, door);
//--------------------------------------------------

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

ALLEGRO_DISPLAY* bkscreen = nullptr;

class BKMAIN {
public:
	BKMAIN() {

		// inicia a biblioteca allegro
		al_init();
		// inicia os modulos
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();
		//instalar perifericos
		al_install_keyboard();

		//criar display
		bkscreen = al_create_display(900, 700);

	}

	void start() {
		// pega o display atual
		ALLEGRO_DISPLAY* tmp = al_get_current_display();
		// e muda para o display da engine
		al_set_target_backbuffer(bkscreen);

		al_draw_line(200,0,200,700,al_map_rgb(48,48,48),3);
		


		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
		// depois devolve a pintura para o display anterior
		al_set_target_backbuffer(tmp);
	}

	~BKMAIN() {
		al_destroy_display(bkscreen);
	}
}ENGINE;

#else

#define getdoor(not_active, not_active)

#endif


#endif
