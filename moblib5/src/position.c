/*
 ------------------------------------------------------
´ |               Biblioteca feita por               | `
  |                                                  |
  | [criador: Bruno Dalagnol]                        |
  | [criado em: 02/11/2022]                          |
  | [ultima revisão: 02/11/2022]                     |
  | [versao: 5.0.0-alp]                              |
  |--------------------------------------------------|
  |                                                  |
  |              /\        /\       ___              |
  |             /--\______/--\     / ,_|             |
  |             |  Y     Y   |    / /                |
  |             |  "==T=="   |   / /                 |
  |	            \____________/  / /                  |
  |	             `|   ----   \ / /                   |
  |               |  ,__,  ,  \ /                    |
  |               |  || |  |\  |                     |
  |	              |__||_|__||__|                     |
`------------------------------------------------------´
*/

#ifndef MOB_POSITION_SOURCE_INCLUDED
#define MOB_POSITION_SOURCE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/types.h"
#include "../inc/safe.h"
#include "../inc/position.h"

#ifdef __cplusplus
extern "C" {
#endif


extern MobPosition* mob_position_create(float x, float y) {
	MobPosition* position = safe_calloc_this(struct _MobPosition);
	position->x = x;
	position->y = y;
	return position;
}


extern MobPositionTraced* mob_position_create_traced(float x, float y, int size, int delay) {
	MobPositionTraced* position_traced = safe_calloc_this(struct _MobPositionTraced);
	position_traced->position = mob_position_create(x, y);
	if (size) {
		position_traced->x = safe_calloc_these(float, size);
		position_traced->y = safe_calloc_these(float, size);
		for (int i = 0; i < size; i++) {
			position_traced->x[i] = x;
			position_traced->y[i] = y;
		}
	}
	else {
		position_traced->x = 0;
		position_traced->y = 0;
	}
	position_traced->size = size;
	position_traced->delay = delay;
	position_traced->delay_count = delay;
	return position_traced;
}


extern MobPositionTraced* mob_position_create_traced_referenced(MobPosition* position, int size, int delay) {
	MobPositionTraced* position_traced = safe_calloc_this(struct _MobPositionTraced);

	position_traced->position = position;

	if (size) {
		position_traced->x = safe_calloc_these(float, size);
		position_traced->y = safe_calloc_these(float, size);
		for (int i = 0; i < size; i++) { position_traced->x[i] = position->x, position_traced->y[i] = position->y; }
	}
	else { position_traced->x = 0, position_traced->y = 0; }
	position_traced->size = size, position_traced->delay = delay, position_traced->delay_count = delay;
	return position_traced;
}


extern void mob_get_moviment_traced(MobPositionTraced* self, MobPosition* pos, uint index) {
	if (index < self->size) {
		pos->x = self->x[index];
		pos->y = self->y[index];
	}
	printf("Index fora do range");
	exit(-1);
}

extern void mob_set_moviment_traced(MobPositionTraced* self, float x, float y) {
	if (self->size > 0) {
		for (sint i = self->size - 1, e = self->size - 2; i > 0; i--, e--) {
			self->x[i] = self->x[e];
			self->y[i] = self->y[e];
		}
		self->x[0] = x, self->y[0] = y;
		return;
	}
	printf("Index fora do range");
	exit(-1);
}

extern void mob_set_moviment_auto_traced(MobPositionTraced* self, float x, float y) {
	self->position->x = x, self->position->y = y;
	if (self->delay_count > 1) {
		self->delay_count--;
		return;
	}
	self->delay_count = self->delay;
	mob_set_moviment_traced(self, x, y);
}

extern void mob_set_moviment_self_traced(MobPositionTraced* self) {
	if (self->delay_count > 1) {
		self->delay_count--;
		return;
	}
	self->delay_count = self->delay;
	mob_set_moviment_traced(self, self->position->x, self->position->y);
}


extern void mob_position_destroy_traced(MobPositionTraced* self) {
	if (self->position) {
		free(self->position);
	}
	if (self->x) {
		free(self->x);
	}
	if (self->y) {
		free(self->y);
	}
}


extern MobDimension* mob_dimension_create(float width, float height) {
	MobDimension* dimension = safe_calloc_this(struct _MobDimension);
	dimension->width = width;
	dimension->height = height;
	return dimension;
}


extern MobForm* mob_form_create(float x, float y, float width, float height) {
	MobForm* form = safe_calloc_this(struct _MobForm);
	form->position = mob_position_create(x, y);
	form->dimension = mob_dimension_create(width, height);
	return form;
}


extern MobForm* mob_form_create_referenced(MobPosition* position, MobDimension* dimension) {
	MobForm* form = safe_calloc_this(struct _MobForm);
	form->position = position;
	form->dimension = dimension;
	return form;
}


extern void mob_form_delete(MobForm* self) {
	if (self->dimension) free(self->dimension);
	if (self->position) free(self->position);
}


int mob_form_side(MobForm* self, MobForm* other_object) {
	int code = OUTER;
	if (self->position->y + self->dimension->height < other_object->position->y) {
		code = code | UP;
	}
	else if (self->position->y > other_object->position->y + other_object->dimension->height) {
		code = code | DOWN;
	}
	if (self->position->x > other_object->position->x + other_object->dimension->width) {
		code = code | RIGHT;
	}
	else if (self->position->x + self->dimension->width < other_object->position->x) {
		code = code | LEFT;
	}
	return code;
}

float mob_form_angle_x(MobForm* self, MobForm* other_object) {
	/* devolve o angulo em relação ao eixo x, anti-horario
	*/

	// pega o ponto central dos quadrados
	float sX = self->position->x + self->dimension->width / 2;
	float sY = self->position->y + self->dimension->height / 2;
	float oX = other_object->position->x + other_object->dimension->width / 2;
	float oY = other_object->position->y + other_object->dimension->height / 2;

	// calcula o angulo em relação ao eixo X
	return (oY - sY) / (oX - sX);
}

float mob_form_angle_y(MobForm* self, MobForm* other_object) {
	/* devolve o angulo em relação ao eixo x, anti-horario
	*/

	// pega o ponto central dos quadrados
	float sX = self->position->x + self->dimension->width / 2;
	float sY = self->position->y + self->dimension->height / 2;
	float oX = other_object->position->x + other_object->dimension->width / 2;
	float oY = other_object->position->y + other_object->dimension->height / 2;

	// calcula o angulo em relação ao eixo X
	return (oX - sX) / (oY - sY);
}

MobPosition mob_form_border_point(MobForm* self, MobForm* other_object) {
	/* devolve a posição da borda que a reta entre os objetos passa
	*/
	float sX = self->position->x + self->dimension->width / 2,
		  sY = self->position->y + self->dimension->height / 2,
		  oX = other_object->position->x + other_object->dimension->width / 2,
		  oY = other_object->position->y + other_object->dimension->height / 2,
		  fX = oX - sX,
          fY = oY - sY,
		  a, ca;

	if (fabs(fX) < fabs(fY)) {
		a = fY / fX;
		ca = self->dimension->height / 2 / a;
		if (sY < oY) {
			// pra baixo
			return (MobPosition) {
				self->position->x + self->dimension->width / 2 + ca,
				self->position->y + self->dimension->height
			};
		}
		else {
			// pra cima
			return (MobPosition) {
				self->position->x + self->dimension->width / 2 - ca,
				self->position->y
			};
		}
	}
	else {
		a = fX / fY;
		ca = self->dimension->width / 2 / a;
		if (sX < oX) {
			// pra frente
			return (MobPosition) {
				self->position->x + self->dimension->width,
				self->position->y + self->dimension->height / 2 + ca
			};
		}
		else {
			// pra tras
			return (MobPosition) {
				self->position->x,
				self->position->y + self->dimension->height / 2 - ca
			};
		}
	}
}


extern MobFormChain* mob_form_create_chain(float x, float y, float width, float height) {
	MobPosition* position = safe_calloc_this(struct _MobPosition);
	MobDimension* dimension = safe_calloc_this(struct _MobDimension);
	MobFormChain* form_chain = safe_calloc_this(struct _MobFormChain);

	position->x = x;
	position->y = y;
	dimension->width = width;
	dimension->height = height;
	form_chain->form.position = position;
	form_chain->form.dimension = dimension;

	return form_chain;
}


extern MobFormChain* mob_form_create_chain_referenced(MobPosition* position, MobDimension* dimension) {
	MobFormChain* form_chain = safe_calloc_this(struct _MobFormChain);
	form_chain->form.position = position;
	form_chain->form.dimension = dimension;
	return form_chain;
}


// destroi a corrente
extern void mob_form_delete_chain(MobFormChain** header) {
	MobFormChain* ptr = 0;
	while (*header) {
		ptr = *header;
		*header = (*header)->next;
		free(ptr);
	}
	header = 0;
}


extern void mob_form_delete_chain_cascaded(MobFormChain** header) {
	MobFormChain* ptr = 0;
	while (*header) {
		ptr = *header;
		*header = (*header)->next;
		free(ptr->form.dimension);
		free(ptr->form.position);
		free(ptr);
	}
	header = 0;
}


// adiciona ao topo da corrente
extern void mob_form_add_to_chain(MobFormChain** header, MobFormChain* self) {
	self->next = *header;
	*header = self;
}


// remove o topo da corrente
extern MobFormChain* mob_form_remove_top_chain(MobFormChain** header) {
	MobFormChain* ptr = *header;
	*header = (*header)->next;
	return ptr;
}


// remove uma posição da corrente
extern MobFormChain* mob_form_remove_reference_chain(MobFormChain** header, MobFormChain* point) {
	MobFormChain* ptr;
	if (*header == point) {
		ptr = *header;
		*header = (*header)->next;
		return ptr;
	}
	ptr = (*header)->next;
	for (MobFormChain *before = *header; ptr; before = ptr, ptr = ptr->next) {
		if (ptr == point) {
			before->next = ptr->next;
			return ptr;
		}
	}
	return 0;
}


#ifdef __cplusplus
}
#endif

#endif //MOB_POSITION_SOURCE_INCLUDED