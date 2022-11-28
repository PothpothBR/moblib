/*
 ------------------------------------------------------
� |               Biblioteca feita por               | `
  |                                                  |
  | [criador: Bruno Dalagnol]                        |
  | [criado em: 02/11/2022]                          |
  | [ultima revis�o: 02/11/2022]                     |
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
`------------------------------------------------------�
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

/** estrutura que agrega informa��o que � possivelmente em comum para varias anima��es
* 
* range - quantidade de celulas que a anima��o ter�
* direction - dire��o da anima��o (MOB_ANIMATE_FORWARD, MOB_ANIMATE_BACK, MOB_ANIMATE_FLIP)
* delay - tempo de execu��o que ira demorar para trocar de celula
* fps - se > 0 faz delay ser definido em segundos
* step - numero de celulas que ser�o puladas, util para micro-otimiza��o e casos especificos
*/
typedef struct _MobAnimateInfo {
	int range, direction, delay, fps, step;
}MobAnimateInfo;

/** estrutura para armazenar uma anima��o
* 
* start - em qual celula a anima��o inicia
* end - em qual celula a anima��o termina
* index - posi��o atual da celula
* flip - usado esclusivamente para o modo MOB_ANIMATE_FLIP
* clock - temporizador para contar o delay entre as celulas
* info - informa��es em comum entre anima��es
*/
typedef struct _MobAnimate {
	int start, end, index, flip;
	MobClock* clock;
	MobAnimateInfo* info;
}MobAnimate;

/** instancia o objeto MobAnimateInfo
*
* range - tamanho da anima��o (em quantidade de celulas)
* direction - dire��o da anima��o
* delay - tempo de execu��o que ira demorar para trocar de celula
* fps - se > 0 faz delay ser definido em segundos
* step - numero de celulas que ser�o puladas, util para micro-otimiza��o e casos especificos
* 
* > o objeto instanciado
*/
MobAnimateInfo* mob_animate_create_info(sint, sint, int, int, sint);

/** instancia o objeto MobAnimate
*
* start - em qual celula a anima��o inicia
* range - tamanho da anima��o (em quantidade de celulas)
* direction - dire��o da anima��o
* delay - tempo de execu��o que ira demorar para trocar de celula
* fps - se > 0 faz delay ser definido em segundos
* step - numero de celulas que ser�o puladas, util para micro-otimiza��o e casos especificos
*
* > o objeto instanciado
*/
MobAnimate* mob_animate_create(sint, sint, sint, int, int, sint);

/** instancia o objeto MobAnimate usando uma referencia j� instanciada de MobAnimateInfo
*
* info - objeto do tipo MobAnimateInfo contendo informa��es pr� definidas
* start - em qual celula a anima��o inicia
*
* > o objeto instanciado
*/
MobAnimate* mob_animate_create_referenced(MobAnimateInfo*, sint);

/** deleta um objeto do tipo MobAnimate. S� faca isso se voce usou mob_animate_create para criar 
* o seu objeto e nao alterou os ponteiros dentro da estrutura em nenhum momento. Caso contrario � do
* dever de quem criou liberar a mem�ria corretamente.
*
* self - objeto a ser deletado
*/
void mob_animate_delete(MobAnimate*);

/** realiza o fluxo da anima��o especificada
*
* self - anima��o a ser executada
*
* > celula atual da anima��o
*/
int mob_animate(MobAnimate*);

#ifdef __cplusplus
}
#endif

#endif //MOB_ANIMATION_HEADER_INCLUDED