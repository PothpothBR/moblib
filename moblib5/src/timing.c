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

#ifndef MOB_TIMING_SOURCE_INCLUDED
#define MOB_TIMING_SOURCE_INCLUDED

#include <stdlib.h>
#include "../inc/timing.h"
#include "../inc/safe.h"

#ifdef __cplusplus
extern "C" {
#endif


extern MobClock* mob_clock_create(int time, int fps, bool reset) {
	MobClock* clock = safe_calloc_this(struct _MobClock);
	if (fps > 0.0) { clock->time = time / fps; }
	else { clock->time = time; }
	if (reset) { clock->counter = time; }
	return clock;
}


extern void mob_clock_charge(MobClock* self) {
	self->counter = 0;
}


extern void mob_clock_reset(MobClock* self) {
	self->counter = self->time;
}


extern void mob_clock_set_time(MobClock* self, int time, int fps) {
	if (fps > 0.0) { self->time = time / fps; }
	else { self->time = time; }
}


extern bool mob_clock_tick(MobClock* self) {
	if (self->counter <= 1) {
		self->counter = self->time;
		return 1;
	}
	else self->counter--;
	return 0;
}


extern bool mob_clock_trigger(MobClock* self) {
	if (self->counter < 1) {
		self->counter = self->time;
		return 1;
	}
	return 0;
}


extern void mob_clock_wait(MobClock* self) {
	if (self->counter > 0) {
		self->counter--;
	}
}


#ifdef __cplusplus
}
#endif

#endif // MOB_TIMING_SOURCE_INCLUDED
