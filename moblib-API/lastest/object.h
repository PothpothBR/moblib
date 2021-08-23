#ifndef OBJECT_H
#define OBJECT_H

#include "id.h"

template <class OBJECT, class PROPERTY, class NAME>
class _Object {

	// retorna a posicao do objeto, se nao existir retorna -1
	int getObjectPos(OBJECT object) {

		for (int i = 0; i < size_object; i++) {
			if (object == *_object[i]) return i;
		}
		return -1;
	}

public:

	OBJECT** _object = nullptr;
	int size_object = 0;
	_Id<PROPERTY, NAME>* _property;
	int size_property = 0;

	// cria um novo objeto
	void newObject(OBJECT object) {

		_object = (OBJECT**)realloc(_object, ++size_object * sizeof(OBJECT*));
		_object[size_object - 1] = (OBJECT*)malloc(sizeof(OBJECT));
		*_object[size_object - 1] = OBJECT(object);

		_property = (_Id<PROPERTY, NAME>*)realloc(_property, ++size_property * sizeof(_Id<PROPERTY, NAME>));
		_property[size_property - 1] = _Id<PROPERTY, NAME>();
		
	}

	// adiciona uma nova propriedade a um objeto especifico
	void newProperty(OBJECT object, PROPERTY property) {
		_property[getObjectPos(object)].newId(property);
	}

	// adiciona um id a propriedade de um objeto especifico
	void addIdInProperty(OBJECT object, PROPERTY property, NAME id) {
		_property[getObjectPos(object)].linkId(id, property);
	}

	//retorna se existe a propriedade no objeto especifico
	bool isPropertyIn(OBJECT object, PROPERTY property) {
		for (int i = 0; i < size_object; i++) {
			if (object == *_object[i])
				return ((_property[i].id(property) < 0) ? false : true);
		}
		return false;
	}

	// retorna o ponteiro do id
	NAME* adrressId(OBJECT object, PROPERTY property, NAME id) {
		for (int i = 0; i < size_object; i++) {
			if (object == *_object[i])
				return _property[i].ptrLink(id, property);
		}
		return nullptr;
	}
};

#endif
