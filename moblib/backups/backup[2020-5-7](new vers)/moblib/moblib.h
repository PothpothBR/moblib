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


#include "sheet.h" //finalizada!
#include "animation.h" //finalizada
#include "moviment.h" // finalizada!
#include "mapping.h" // finalizado!

template <class T>
class OBJECT {
public:
	ANIMATION::ANIMATE **animation = nullptr;
	SHEET *sheet = nullptr;
	ANIMATION::INSTANCE *instance = nullptr;
	MOVIMENT::FORM *format = nullptr;
	T *moviment = nullptr;
	MAP::MAPPING *mapping = nullptr;
	sint animSize = 0;

	OBJECT(sint animation_buffer_size) { animSize = animation_buffer_size; }

	~OBJECT() {
		for (int i = 0;i < animSize;i++) {
			delete animation[i];
		}
		free(animation);

		delete sheet;
		delete format;
		delete moviment;
		delete mapping;
		delete instance;
	}
};


#endif
