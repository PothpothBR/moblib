/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
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
#ifndef MOBLIB_H
#define MOBLIB_H

#include "thread.h" // semi finalizado!
#include "sheet.h" //finalizada!
#include "animation.h" //finalizada
#include "moviment.h" // finalizada!
#include "colision.h" // em teste!
#include "mapping.h" // finalizado!
#include "timing.h" // finalizada!

#define SECtoFPS(sec) sec/0.017 // taxa de 60 FPS
#define BIGGER(a, b) (a > b) ? a : b // retorna o maior / menor
#define SMALLER(a, b) (a < b) ? a : b
#define ROUNDUP(a) (int)a+a%1 // aredonda para cima
typedef short int sint;

template <class T = MOVIMENT::INSTANCE>
class OBJECT {
public:
	ANIM::ANIMATE **animation = nullptr;
	SHEET *sheet = nullptr;
	ANIM::INSTANCE *instance = nullptr;
	COLLISION::COLID *format = nullptr;
	T *moviment = nullptr;
	MAPPING *mapping = nullptr;
	sint animSize = 0;

	OBJECT(sint anim_bff_size) {
		animSize = anim_bff_size;
		animation = (ANIM::ANIMATE**)calloc(anim_bff_size, sizeof(ANIM::ANIMATE*));
	}

	~OBJECT() {
		for (int i = 0;i < animSize;i++) {
			delete animation[i];
		}
		free(animation);

		if (sheet)delete sheet;
		if (format)delete format;
		if (moviment)delete moviment;
		if (mapping)delete mapping;
		if (instance)delete instance;
	}
};


#endif
