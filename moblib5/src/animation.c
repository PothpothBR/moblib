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

#ifndef MOB_ANIMATION_SOURCE_INCLUDED
#define MOB_ANIMATION_SOURCE_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "../inc/types.h"
#include "../inc/safe.h"
#include "../inc/animation.h"
#include "../inc/timing.h"

#ifdef __cplusplus
extern "C" {
#endif


extern MobAnimateInfo* mob_animate_create_info(sint range, sint direction, int delay, int fps, sint step) {
	MobAnimateInfo* animate_info = safe_calloc_this(struct _MobAnimateInfo);

	animate_info->direction = direction;
	animate_info->range = range - 1;
	animate_info->delay = delay;
	animate_info->step = step + 1;
	animate_info->fps = fps;
	return animate_info;
}


extern MobAnimate* mob_animate_create(sint start, sint range, sint direction, int delay, int fps, sint step) {
	MobAnimate* animate = safe_calloc_this(struct _MobAnimate);
	MobAnimateInfo* animate_info = safe_calloc_this(struct _MobAnimateInfo);

	animate_info->direction = direction;
	animate_info->range = range - 1;
	animate_info->delay = delay;
	animate_info->step = step + 1;
	animate_info->fps = fps;

	if (animate_info->direction == MOB_ANIMATE_FLIP) {
		animate->index = start + 1;
	}
	else {
		animate->index = start - 1;
	}

	animate->info = animate_info;
	animate->start = start;
	animate->end = start + animate_info->range;
	animate->flip = -animate_info->step;
	animate->clock = mob_clock_create(animate_info->delay, animate_info->fps, false);
	return animate;
}


extern MobAnimate* mob_animate_create_referenced(MobAnimateInfo* info, sint start) {
	MobAnimate* animate = safe_calloc_this(struct _MobAnimate);

	if (info->direction == MOB_ANIMATE_FLIP) {
		animate->index = start + 1;
	}
	else {
		animate->index = start - 1;
	}

	animate->info = info;
	animate->start = start;
	animate->end = start + info->range;
	animate->flip = -(info->step);
	animate->clock = mob_clock_create(info->delay, info->fps, false);
	return animate;
}


extern void mob_animate_delete(MobAnimate* self) {
	free(self->clock);
	free(self->info);
}


extern int mob_animate(MobAnimate* self) {
	if (!mob_clock_tick(self->clock)) {
		return self->index;
	}
	switch (self->info->direction) {
	case MOB_ANIMATE_FORWARD:
		self->index += self->info->step;
		if (self->index > self->end) self->index = self->start;
		return self->index;
	case MOB_ANIMATE_BACK:
		self->index -= self->info->step;
		if (self->index < self->start) self->index = self->end;
		return self->index;
	case MOB_ANIMATE_FLIP:
		if (self->index + self->flip < self->start || self->index + self->flip > self->end) {
			self->flip *= -1;
		}
		self->index += self->flip;
		return self->index;
	}
	printf("Erro ao selecionar flag para animação! <mob_animate(direction=%i)>", self->info->direction);
	exit(-1);
}


#ifdef __cplusplus
}
#endif

#endif //MOB_ANIMATION_SOURCE_INCLUDED