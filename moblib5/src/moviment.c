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

#ifndef MOB_MOVIMENT_SOURCE_INCLUDED
#define MOB_MOVIMENT_SOURCE_INCLUDED

#include <stdlib.h>
#include <math.h>
#include "../inc/types.h"
#include "../inc/safe.h"
#include "../inc/collision.h"
#include "../inc/moviment.h"

#ifdef __cplusplus
extern "C" {
#endif


#define make_moviment_functions(_Construct, _ConstructReferenced, _Destruct, _Type) \
extern _Type* _Construct(float x, float y, int trace_size, int trace_delay, float vel) { \
	_Type* moviment = safe_calloc_this(_Type); \
	moviment->trace = mob_position_create_traced(x, y, trace_size, trace_delay); \
	return moviment; \
} \
extern _Type* _ConstructReferenced(MobPositionTraced* position, float vel) { \
	_Type* moviment = safe_calloc_this(_Type); \
	moviment->trace = position; \
	return moviment; \
} \
extern void _Destruct(_Type* self) { \
	free(self->trace); \
}


static const float moviment_x[8] = { 0,  -1,  0,  1, -0.707107f ,  0.707107f, -0.707107f ,  0.707107f };
static const float moviment_y[8] = { -1,  0,  1,  0, -0.707107f , -0.707107f,  0.707107f ,  0.707107f };


make_moviment_functions(
	mob_moviment_create_axes,
	mob_moviment_create_axes_referenced,
	mob_moviment_delete_axes,
	struct _MobMovimentAxis
);


make_moviment_functions(
	mob_moviment_create_auto,
	mob_moviment_create_auto_referenced,
	mob_moviment_delete_auto,
	struct _MobMovimentAuto
);


// metodo para movimentar
void mob_moviment_run_axes(MobMovimentAxis* self) {
	self->trace->position->x += moviment_x[self->active] * self->vel;
	self->trace->position->y += moviment_y[self->active] * self->vel;
}

// metodo para movimentar, com sistema de colizao com multiplos objetos auto implementado
void mob_moviment_run_keyboard_with_collision_chain(MobMovimentAxis* self, MobCollision* self_box, MobFormChain* list_box) { // fazer como define
	mob_reload_collision(self_box);
	mob_moviment_run_keyboard(self);
	mob_collision(self_box, self_box, list_box);
}

// necessario de usar após realizar um teste de colizão para atualizar o sistema de colizao
// se usar mob_run() com colizão, a colizao ja se auto atualiza
void mob_moviment_reload_collision_axes(MobCollision* self) {
	*self->trace->x = self->trace->position->x;
	*self->trace->y = self->trace->position->y;
}

// recarrega a colizao de um objeto colizor a partir da movimentacao de outro objeto
void mob_moviment_reload_collision_axes_mirror(MobMovimentAxis* self, MobCollision* collision) {
	*collision->trace->x = collision->trace->position->x + moviment_x[self->active] * self->vel;
	*collision->trace->y = collision->trace->position->y + moviment_x[self->active] * self->vel;
}

void mob_reload_collision_auto_mirror(MobMovimentAuto* self, MobCollision* collision) {
	if (!self->stop) {
		*collision->trace->x = self->vuX;
		*collision->trace->y = self->vuY;
	}
}

// metodo para modificar a velocidade
void mob_moviment_velocity_auto(MobMovimentAuto* self, float vel) { // terminar
	if (self->dX && vel != self->vel) {
		self->vel = vel;
		self->vuX = self->vel / self->dH * self->dX;
		self->vuY = self->vel / self->dH * self->dY; //divisao por 0
	}
}
// metodo para modificar a direcao de movimeto
void mob_moviment_direction_auto(MobMovimentAuto* self, float x, float y, float vel) { // terminar

	if (x == self->trace->position->x && y == self->trace->position->y) return;

	self->vel = vel;
	self->stop = false;

	self->dX = x - self->trace->position->x;
	self->dY = y - self->trace->position->y;
	self->fX = x;
	self->fY = y;

	self->fH = (float)hypot(x, y);
	self->dH = (float)hypot(self->dX, self->dY);

	self->vuX = self->vel / (float)(self->dH * self->dX + 0.000001);
	self->vuY = self->vel / (float)(self->dH * self->dY + 0.000001);
	x = self->dX;
	y = self->dY;
}

/** funcao para movimentar um MobMovimentAuto objeto, para ao chegar ao destino e seta a flag self->stop como true
* 
* self - objeto do tipo MobMovimentAuto
*/
void mob_moviment_run_auto(MobMovimentAuto* self) {
	self->trace->position->x += self->vuX;
	self->trace->position->y += self->vuY;

	if (self->trace->position->x - self->fX + self->trace->position->y - self->fY > 0) {
		self->trace->position->x = self->fX;
		self->trace->position->y = self->fY;
		self->stop = true;
	}
}

#ifdef __cplusplus
}
#endif

#endif //MOB_MOVIMENT_SOURCE_INCLUDED
