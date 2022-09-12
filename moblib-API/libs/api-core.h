#ifndef API_CORE_H
#define API_CORE_H

#include <cstdlib>
#include "id.h"
#include "object.h"
#include "animations.h"
#include "C:/Users/Bruno/Google Drive/backups/moblib/lastest/moblib.h"

//redefinicao das macros

#define _forward ANIM::FORWARD
#define _back ANIM::BACK
#define _flip ANIM::FLIP
#define none -1

class Core {

public:
	_Animation* _animation = nullptr;
	float fps = 0;
	_Object<const char*, int, const char*> *_objects = nullptr;
	/*
	 * 0 >> animation
	 * 1 >> moviment
	 */

	Core(float fps) {
		// iniciar a animacao:
		_animation  = new _Animation();
		_animation->setFPS(fps);
		this->fps = fps;
		_objects = new _Object<const char*, int, const char*>();
	}

	~Core() {
		//liberar as ramificacoes:
		delete _animation;
		delete _objects;
	}

	//cria um novo objeto
	void newObject(const char* id) {
		_objects->newObject(id);
	}

	// cria uma animacao para o objeto target
	void newAnimation(const char* object, const char* id, int start, int range, int direction = ANIM::FLIP, float delay = 0, int jump = 0) {
		if (!_objects->isPropertyIn(object, 0)) {
			_objects->newProperty(object, 0);
		}
		_objects->addIdInProperty(object, 0, id);
		_animation->newAnimation(_objects->adrressId(object, 0, id), start, range, direction, delay, jump);
	}

	// modifica a animation, se o valor for < 0 nao sera modificado
	void modAnimation(const char* object, const char* id, int start, int range = none, int direction = none, float delay = none, int jump = none) {
		_animation->modAnimation(_objects->adrressId(object, 0, id), start, range, direction, delay, jump);
	}

	//retorna o index da animacao para o id especifico
	int animeIndex(const char* object, const char* id) {
		return _animation->getAnimation(_objects->adrressId(object, 0, id))->index;
	}

	// executa o fluxo de todos os objetos
	void flow() {
		// anima as animacoes
		for (int i = 0; i < _animation->anim_size; i++) {
			ANIM::anim(_animation->_animate[i]);
		}
	}
};

#endif