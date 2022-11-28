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

#ifndef MOB_TIMING_HEADER_INCLUDED
#define MOB_TIMING_HEADER_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** estrutura para contar
*
* time - ticks até o clock virar
* counter - contador que representa a posição atual do clock
*/
typedef struct _MobClock {
	int time;
	int counter;
}MobClock;

/** instancia o objeto MobClock, vem carregado por padrao
*
* time - tempo ate a virada do clock
* fps - se definido time sera contado em segundos
* reset - se definido o clock nao iniciara carregado
*
* self - estrutura MobClock
*
* > MobClock*
*/
MobClock* mob_clock_create(int, int, bool);

/** zera o clock, isso faz com que a proxima chamada de mob_trigger_clock retorne 1
*
* self - estrutura MobClock
*
* > void
*/
void mob_clock_charge(MobClock*);

/** faz o clock voltar ao inicio da contagem
*
* self - estrutura MobClock
*
* > void
*/
void mob_clock_reset(MobClock*);

/** define um valor especifico para o clock, se fps > 0 altere o tempo para executar segundo o fps especificado
*
* time - tempo para o clock realizar uma volta completa (trigger)
* fps (opcional) - muda time para se comportar segundo o fps
* self - estrutura MobClock
*
* > void
*/
void mob_clock_set_time(MobClock*, int, int);

/** decrementa o clock até que chegue a 0, recomessa a contagem nesse ponto
*
* self - estrutura MobClock
*
* > 0 | 1
*/
bool mob_clock_tick(MobClock*);

/** retorna 1 se o clock chegar a zero, caso contrario retorna 0
*
* self - estrutura MobClock
*
* > 0 | 1
*/
bool mob_clock_trigger(MobClock*);

/** decrementa o clock até que chegue a 0, para nesse ponto
*
* self - estrutura MobClock
*
* > void
*/
void mob_clock_wait(MobClock*);

#ifdef __cplusplus
}
#endif

#endif //MOB_TIMING_HEADER_INCLUDED