/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     / _|              |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/
#ifndef POSITION_H
#define POSITION_H

class MOB_POSITION {
public:
	float x = 0, y = 0;
	MOB_POSITION(){}
	MOB_POSITION(float x, float y) { this->x = x, this->y = y; }
};

class MOB_DIMENSION {
public:
	float width = 0, height = 0;
	MOB_DIMENSION(){}
	MOB_DIMENSION(float width, float height) { this->width = width, this->height = height; }
};

class MOB_FORM {
public:
	MOB_POSITION* position = nullptr;
	MOB_DIMENSION* dimension = nullptr;

	MOB_FORM() {}
	MOB_FORM(MOB_POSITION* position, MOB_DIMENSION* dimension) { this->position = position, this->dimension = dimension; }
};

// classe simples em corrente para pontos de colizao
class MOB_FORM_CHAIN {
public:
	MOB_FORM_CHAIN* next = nullptr;
	MOB_FORM form;
	~MOB_FORM_CHAIN() {
		delete form.position;
		delete form.dimension;
	}
};

MOB_FORM_CHAIN* mob_create_form_chain(float x, float y, float width, int height) {
	MOB_FORM_CHAIN* self = new MOB_FORM_CHAIN;
	self->form.position = new MOB_POSITION(x, y);
	self->form.dimension = new MOB_DIMENSION(width, height);
	return self;
}

// adiciona ao topo da corrente
void mob_add_to_chain(MOB_FORM_CHAIN** header, MOB_FORM_CHAIN* self) {
	self->next = *header;
	*header = self;
}

// destroi a corrente
void mod_delete_chain(MOB_FORM_CHAIN** header) {
	MOB_FORM_CHAIN* ptr = nullptr;
	while (*header) {
		ptr = *header;
		*header = (*header)->next;
		delete ptr;
	}
}

// remove o topo da corrente
void mod_remove_chain_header(MOB_FORM_CHAIN** header) {
	MOB_FORM_CHAIN* ptr = *header;
	*header = (*header)->next;
	delete ptr;
}

// remove uma posição da corrente
void mod_delete_chain_point(MOB_FORM_CHAIN** header, MOB_FORM_CHAIN* point) {
	if (*header == point) {
		mod_remove_chain_header(header);
		return;
	}
	for (MOB_FORM_CHAIN* ptr = (*header)->next, *before = *header; ptr; before = ptr, ptr = ptr->next) {
		if (ptr == point) {
			before->next = ptr->next;
			delete ptr;
			return;
		}
	}
}
#endif //POSITION_H