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

#ifndef MOB_MOVIMENT_HEADER_INCLUDED
#define MOB_MOVIMENT_HEADER_INCLUDED

#include "../inc/types.h"
#include "../inc/position.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MOB_MOVIMENT_DIRECTION_ALL true
#define MOB_MOVIMENT_DIRECTION_AXIS false

#define MOB_MOVIMENT_UP 0
#define MOB_MOVIMENT_LEFT 1
#define MOB_MOVIMENT_DOWN 2
#define MOB_MOVIMENT_RIGHT 3

#define MOB_MOVIMENT_UP_LEFT 4
#define MOB_MOVIMENT_UP_RIGHT 5
#define MOB_MOVIMENT_DOWN_LEFT 6
#define MOB_MOVIMENT_DOWN_RIGHT 7

#define make_moviment_prototypes(_Construct, _ConstructReferenced, _Destruct, _Type) \
_Type* _Construct(float, float, int, int, float); \
_Type* _ConstructReferenced(MobPositionTraced*, float); \
void _Destruct(_Type*)

#define mob_moviment_reload_collision_axes_auto(moviment, collision) \
	(collision->reference == collision->trace->position) ? \
		mob_moviment_reload_collision_axes(moviment) : \
		mob_moviment_reload_collision_axes_mirror(moviment, collision)

#define mob_moviment_run_axes_with_colision(moviment, collision, otr_position, otr_dimension) \
	mob_moviment_reload_collision_axes_auto(moviment, collision); \
	mob_moviment_run_axes(moviment); \
	mob_collizion_auto(collision, otr_position, otr_dimension)

typedef struct _MobMovimentAxis {
	MobPositionTraced* trace;
	float vel;
	bool active;
}MobMovimentAxis;


typedef struct _MobMovimentAuto {
	MobPositionTraced* trace;
	float fX, fY, fH,
		dX, dY, dH,
		vuX, vuY, vel;
	bool stop;
	sint dirMiddle, dirExact;
}MobMovimentAuto;


make_moviment_prototypes(
	mob_moviment_create_axes,
	mob_moviment_create_axes_referenced,
	mob_moviment_delete_axes,
	struct _MobMovimentAxis
);


make_moviment_prototypes(
	mob_moviment_create_auto,
	mob_moviment_create_auto_referenced,
	mob_moviment_delete_auto,
	struct _MobMovimentAuto
);


void mob_moviment_run_axes(MobMovimentAxis*);

void mob_moviment_velocity_auto(MobMovimentAuto*, float);

void mob_moviment_direction_auto(MobMovimentAuto*, float, float, float);

void mob_moviment_run_auto(MobMovimentAuto*);

#ifdef __cplusplus
}
#endif


#endif //MOB_MOVIMENT_HEADER_INCLUDED