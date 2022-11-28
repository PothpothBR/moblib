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

#ifndef MOB_COLLISION_SOURCE_INCLUDED
#define MOB_COLLISION_SOURCE_INCLUDED

#include "../inc/safe.h"
#include "../inc/types.h"
#include "../inc/position.h"
#include "../inc/collision.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern MobCollision* mob_collision_create(float x, float y, float width, float height, float reference_x, float reference_y) {
	MobCollision* colisor = safe_calloc_this(struct _MobCollision);
	colisor->trace = mob_position_create_traced(x, y, 1, 0);
	colisor->dimension = mob_dimension_create(width, height);
	colisor->reference = mob_position_create(reference_x, reference_y);
	colisor->direction = 0;
	return colisor;
}

extern MobCollision* mob_collision_create_referenced(MobPosition *position, MobForm *dimension, MobPosition *reference) {
	MobCollision* colisor = safe_calloc_this(struct _MobCollision);
	colisor->trace = mob_position_create_traced_referenced(position, 1, 0);
	colisor->dimension = dimension;
	colisor->reference = reference;
	colisor->direction = 0;
	return colisor;
}

extern MobCollision* mob_collision_create_traced_referenced(MobPositionTraced* trace, MobForm* dimension, MobPosition* reference) {
	MobCollision* colisor = safe_calloc_this(struct _MobCollision);
	colisor->trace = trace;
	colisor->dimension = dimension;
	colisor->reference = reference;
	colisor->direction = 0;
	return colisor;
}

usint mob_collision_inspector(MobCollision* self, MobPosition* other_position, MobDimension* other_dimension) {
	bool trail_side[4] = {
		*self->trace->x + self->dimension->height <= other_position->y,
		*self->trace->x >= other_position->x + other_dimension->width,
		*self->trace->y >= other_position->y + other_dimension->height,
		*self->trace->x + self->dimension->width <= other_position->x
	};

	bool side[4] = {
		self->trace->position->y + self->dimension->height <= other_position->y,
		self->trace->position->x >= other_position->x + other_dimension->width,
		self->trace->position->y >= other_position->y + other_dimension->height,
		self->trace->position->x + self->dimension->width <= other_position->x
	};

	bool allside = side[0] || side[1] || side[2] || side[3];

	if (trail_side[0] && // cima
		((side[2] && !side[3] && !side[1]) || // colizao em eixos
			(!trail_side[1] && !trail_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) || // colizao em intercessoes
			!allside)) { // colizao interna
		return UP;
	}
	if (trail_side[1] && // frente
		((side[3] && !side[2] && !side[0]) ||
			(!trail_side[0] && !trail_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
			!allside)) {
		return RIGHT;
	}
	if (trail_side[2] && // baixo 
		((side[0] && !side[3] && !side[1]) ||
			(!trail_side[1] && !trail_side[3] && (side[1] || side[3]) && !side[0] && !side[2]) ||
			!allside)) {
		return DOWN;
	}
	if (trail_side[3] && // atras
		((side[1] && !side[2] && !side[0]) ||
			(!trail_side[0] && !trail_side[2] && (side[0] || side[2]) && !side[1] && !side[3]) ||
			!allside)) {
		return LEFT;
	}
	return OUTER;
}

// colisao avancada, sem gosth.
usint mob_collision(MobCollision* self, MobPosition* other_position, MobDimension* other_dimension) {

	switch (mob_collision_inspector(self, other_position, other_dimension)) {
	case OUTER: return OUTER;
	case UP:
		self->reference->y = other_position->y - self->dimension->height - 1;
		return UP;
	case RIGHT:
		self->reference->x = other_position->x + other_dimension->width + 1 - self->trace->position->x;
		return RIGHT;
	case DOWN:
		self->reference->y = other_position->y + other_dimension->height + 1 - self->trace->position->y;
		return DOWN;
	case LEFT:
		self->reference->x = other_position->x - self->dimension->width - 1 - self->trace->position->x;
		return LEFT;
	}

	printf("Colizão nao teve um retorno apropriado!");
	exit(-1);
}

usint mob_collision_mirror(MobCollision* self, MobPosition* other_position, MobDimension* other_dimension) {

	switch (mob_collision_inspector(self, other_position, other_dimension)) {
	case OUTER: return OUTER;
	case UP:
		self->reference->y -= other_position->y - self->dimension->height - 1 - self->trace->position->y;
		return UP;
	case RIGHT:
		self->reference->x -= other_position->x + other_dimension->width + 1 - self->trace->position->x;
		return RIGHT;
	case DOWN:
		self->reference->y -= other_position->y + other_dimension->height + 1 - self->trace->position->y;
		return DOWN;
	case LEFT:
		self->reference->x -= other_position->x - self->dimension->width - 1 - self->trace->position->x;
		return LEFT;
	}

	printf("Colizão nao teve um retorno apropriado!");
	exit(-1);
}

#ifdef __cplusplus
}
#endif

#endif //MOB_COLLISION_SOURCE_INCLUDED