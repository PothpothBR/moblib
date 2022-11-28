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

#ifndef MOB_ANIMATION_HEADER_INCLUDED
#define MOB_ANIMATION_HEADER_INCLUDED

#include "types.h"
#include "timing.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MOB_ANIMATE_FORWARD 0
#define MOB_ANIMATE_BACK 1
#define MOB_ANIMATE_FLIP 2

/** estrutura que agrega informação que é possivelmente em comum para varias animações
* 
* range - quantidade de celulas que a animação terá
* direction - direção da animação (MOB_ANIMATE_FORWARD, MOB_ANIMATE_BACK, MOB_ANIMATE_FLIP)
* delay - tempo de execução que ira demorar para trocar de celula
* fps - se > 0 faz delay ser definido em segundos
* step - numero de celulas que serão puladas, util para micro-otimização e casos especificos
*/
typedef struct _MobAnimateInfo {
	int range, direction, delay, fps, step;
}MobAnimateInfo;

/** estrutura para armazenar uma animação
* 
* start - em qual celula a animação inicia
* end - em qual celula a animação termina
* index - posição atual da celula
* flip - usado esclusivamente para o modo MOB_ANIMATE_FLIP
* clock - temporizador para contar o delay entre as celulas
* info - informações em comum entre animações
*/
typedef struct _MobAnimate {
	int start, end, index, flip;
	MobClock* clock;
	MobAnimateInfo* info;
}MobAnimate;

/** instancia o objeto MobAnimateInfo
*
* range - tamanho da animação (em quantidade de celulas)
* direction - direção da animação
* delay - tempo de execução que ira demorar para trocar de celula
* fps - se > 0 faz delay ser definido em segundos
* step - numero de celulas que serão puladas, util para micro-otimização e casos especificos
* 
* > o objeto instanciado
*/
MobAnimateInfo* mob_animate_create_info(sint, sint, int, int, sint);

/** instancia o objeto MobAnimate
*
* start - em qual celula a animação inicia
* range - tamanho da animação (em quantidade de celulas)
* direction - direção da animação
* delay - tempo de execução que ira demorar para trocar de celula
* fps - se > 0 faz delay ser definido em segundos
* step - numero de celulas que serão puladas, util para micro-otimização e casos especificos
*
* > o objeto instanciado
*/
MobAnimate* mob_animate_create(sint, sint, sint, int, int, sint);

/** instancia o objeto MobAnimate usando uma referencia já instanciada de MobAnimateInfo
*
* info - objeto do tipo MobAnimateInfo contendo informações pré definidas
* start - em qual celula a animação inicia
*
* > o objeto instanciado
*/
MobAnimate* mob_animate_create_referenced(MobAnimateInfo*, sint);

/** deleta um objeto do tipo MobAnimate. Só faca isso se voce usou mob_animate_create para criar 
* o seu objeto e nao alterou os ponteiros dentro da estrutura em nenhum momento. Caso contrario é do
* dever de quem criou liberar a memória corretamente.
*
* self - objeto a ser deletado
*/
void mob_animate_delete(MobAnimate*);

/** realiza o fluxo da animação especificada
*
* self - animação a ser executada
*
* > celula atual da animação
*/
int mob_animate(MobAnimate*);

#ifdef __cplusplus
}
#endif

#endif //MOB_ANIMATION_HEADER_INCLUDED