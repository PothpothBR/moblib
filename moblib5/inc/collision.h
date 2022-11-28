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

#ifndef MOB_COLLISION_HEADER_INCLUDED
#define MOB_COLLISION_HEADER_INCLUDED

#include "types.h"
#include "position.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mob_collizion_auto(collision, otr_position, otr_dimension) \
	(collision->reference == collision->trace->position) ? \
		mob_collision(collision, otr_position, otr_dimension) : \
		mob_collision_mirror(collision, otr_position, otr_dimension)

typedef struct _MobCollision {
	MobPositionTraced* trace;
	MobDimension* dimension;
	MobPosition* reference;
	int direction;
}MobCollision;

extern MobCollision* mob_collision_create(float x, float y, float width, float height, float reference_x, float reference_y);
extern MobCollision* mob_collision_create_referenced(MobPosition* position, MobForm* dimension, MobPosition* reference);
extern MobCollision* mob_collision_create_traced_referenced(MobPositionTraced* trace, MobForm* dimension, MobPosition* reference);

/** verifica se um dois quadrilateros se sobrepoem
* 
* x1, y1, w1, h1 - numeros referentes a x, y, largura, altura
* x2, y2, w2, h2 - numeros referentes a x, y, largura, altura
*/
#define mob_collid_out(x1, y1, w1, h1, x2, y2, w2, h2) (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2)

/** verifica se um quadrilatero especifico(ou parte do mesmo) saiu de outro quadrilatero
* 
* x1, y1, w1, h1 - numeros referentes a x, y, largura, altura
* x2, y2, w2, h2 - numeros referentes a x, y, largura, altura
*/
#define mob_collid_in(x1, y1, w1, h1, x2, y2, w2, h2) !(x1 > x2 && x1 + w1 < x2 + w2 && y1 > y2 && y1 + w1 < y2 + w2)

/** colisao especifica para os eixos. verifica se uma duas linhas se sobrepoem
* 
* a1, l1 - numeros referentes a posição no eixo, largura
* a2, l2 - numeros referentes a posição no eixo, largura
*/
#define mob_collid_in_axes(a1, l1, a2, l2) !(a1 > a2 && a1 + l1 < a2 + l2)

/** colisao especifica para os eixos, com colisao externa. se uma linha especifica(ou parte do mesma) saiu de outra linha
* 
* a1, l1 - numeros referentes a posição no eixo, largura
* a2, l2 - numeros referentes a posição no eixo, largura
*/
#define mob_collid_out_axes(a1, l1, a2, l2) !(a1 < a2 + l2 && a1 + l1 > a2)

/** verifica se um dois quadrilateros se sobrepoem
* 
* self1 - objeto do tipo MobForm
* self2 - objeto do tipo MobForm
*/
#define mob_collid_references(self1, self2) \
	(self1->position->x < self2->position->x + self2->dimension->width && \
	 self1->position->x + self1->dimension->width > self2->position->x && \
	 self1->position->y < self2->position->y + self2->dimension->height && \
	 self1->position->y + self1->dimension->height > self2->position->y)

/** verifica se um dois quadrilateros se sobrepoem
* 
* self1 - objeto do tipo MobForm
* x2, y2, w2, h2 - numeros referentes a x, y, largura, altura
*/
#define mob_collid_reference(self1, x2, y2, w2, h2) \
	(self1->position->x < x2 + w2 &&\
	 self1->position->x + self1->dimension->width > x2 && \
	 self1->position->y < y2 + h2 && \
	 self1->position->y + self1->dimension->height > y2)

/** realiza o fluxo de colizão entre um objeto MobCollision e MobForm
*
* self1 - objeto do tipo MobForm
* x2, y2, w2, h2 - numeros referentes a x, y, largura, altura
*/
#define mob_collision_with_form(self, other_form) mob_collision(self, other_form->position, other_form->dimension);

/** realiza o fluxo de colizão para 2 objetos do tipo MobCollizion
*
* self1 - objeto do tipo MobForm
* x2, y2, w2, h2 - numeros referentes a x, y, largura, altura
*/
#define mob_collision_pair(self, other_collision) mob_collision(self, other_collision->trace->position, other_collision->dimension);

/** realiza o fluxo de colizão e retorna a posição da colizão
* utilizando as flags de posição do types.h
*
* self1 - objeto do tipo MobForm
* x2, y2, w2, h2 - numeros referentes a x, y, largura, altura
*/
usint mob_collision_inspector(MobCollision* self, MobPosition* other_position, MobDimension* other_dimension);
usint mob_collision(MobCollision* self, MobPosition* other_position, MobDimension* other_dimension);

#ifdef __cplusplus
}
#endif

#endif //MOB_COLLISION_HEADER_INCLUDED
