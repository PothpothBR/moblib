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

#ifndef MOB_POSITION_HEADER_INCLUDED
#define MOB_POSITION_HEADER_INCLUDED

#include "../inc/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** estrutura para armazenar um ponto cartografico
*
* x - eixo x
* y - eixo y
*/
typedef struct _MobPosition {
	float x, y;
}MobPosition;

/** estrutura para armazenar o traco de um ponto
*
* position - ponto do tipo MobPosition;
* x - vetor de posições para o eixo x
* y - vetor de posições para o eixo y
* size - tamanho do traço armazendo
* delay - tempo até o traço ser atualizado
* delay_count - variavel interna para contar o tempo para delay
*/
typedef struct _MobPositionTraced {
	MobPosition* position;
	float* x, *y; //TODO: mudar para MobPosition*
	uint size, delay, delay_count; //TODO: mudar de delay_count para clock, unificar todo o sistema em um unico clock?
}MobPositionTraced;

/** estrutura para armazenar dimensões de uma forma
*
* width - largura
* height - altura
*/
typedef struct _MobDimension {
	float width, height;
}MobDimension;

/** estrutura para armazenar uma forma completa
*
* position - posição da forma do tipo MobPosition
* dimension - dimensão da forma do tipo MobDimension
*/
typedef struct _MobForm {
	MobPosition* position;
	MobDimension* dimension;
}MobForm;

/** estrutura para armazenar um ponto cartografico
*
* next - proxima instancia da corrente
* form - forma armazenada pela corrente
*/
typedef struct _MobFormChain {
	struct _MobFormChain* next;
	MobForm form;
}MobFormChain;

/** instancia o objeto MobPosition
*
* x - eixo x
* y - eixo y
*
* > o objeto instanciado
*/
MobPosition* mob_position_create(float, float);

/** instancia o objeto MobPosition
*
* width - largura
* height - altura
*
* > o objeto instanciado
*/
MobDimension* mob_dimension_create(float, float);

/** instancia o objeto MobPositionTraced
*
* x - valor inicial para todas as posições no eixo x
* y - valor inicial para todas as posições no eixo y
* size - tamanho do traço armazendo
* delay - tempo até o traço ser atualizado
*
* > o objeto instanciado
*/
MobPositionTraced* mob_position_create_traced(float, float, int, int);

/** instancia o objeto MobPositionTraced usando um MobPosition já instanciado.
* fica de responsabilidade de quem chamou a função liberar corretamente a memória de MobPosition
*
* position - objeto MobPosition.
* size - tamanho do traço armazendo
* delay - tempo até o traço ser atualizado
*
* > o objeto instanciado
*/
MobPositionTraced* mob_position_create_traced_referenced(MobPosition*, int, int);

/** retorna o ponto na posição <index>.
*
* self - objeto MobPositionTraced.
* pos - objeto que ira receber a posição
* index - posição
*/
void mob_get_moviment_traced(MobPositionTraced*, MobPosition*, uint);

/** adiciona o movimento ao inicio a fila, e remove o ultimo
*
* self - objeto MobPositionTraced.
* x - valor para o eixo x
* y - valor para o eixo y
*/
void mob_set_moviment_traced(MobPositionTraced*, float, float);

/** adiciona o movimento ao inicio a fila, e remove o ultimo, atualiza x, y para position
*
* self - objeto MobPositionTraced.
* x - valor para o eixo x
* y - valor para o eixo y
*/
void mob_set_moviment_auto_traced(MobPositionTraced*, float, float);

/** adiciona o movimento ao inicio a fila, e remove o ultimo, atualiza o x, y com o valor de position
*
* self - objeto MobPositionTraced.
*/
void mob_set_moviment_self_traced(MobPositionTraced*);

/** libera a memória da pilha
*
* self - objeto MobPositionTraced.
*/
void mob_position_destroy_traced(MobPositionTraced*);

/** instancia o objeto MobShape.
*
* x - valor para o eixo x
* y - valor para o eixo y
* width - largura
* height - altura
* 
* > o objeto instanciado
*/
MobForm* mob_form_create(float, float, float, float);

/** instancia o objeto MobShape usando um MobPosition e MobDimension já instanciado.
* fica de responsabilidade de quem chamou a função liberar corretamente a memória de MobPosition e MobDimension
*
* position - objeto do tipo MobPosition
* dimension - objeto do tipo MobDimensions
*
* > o objeto instanciado
*/
MobForm* mob_form_create_referenced(MobPosition*, MobDimension*);

/** libera a memória da forma
*
* self - objeto MobShape.
*/
void mob_form_delete(MobForm*);

/** instancia o objeto MobShapeChain, uma lista encadeada de forms.
*
* x - valor para o eixo x do head
* y - valor para o eixo y do head
* width - largura do head
* height - altura do head
*
* > o objeto instanciado
*/
MobFormChain* mob_form_create_chain(float, float, float, float);

/** instancia o objeto MobShapeChain, uma lista encadeada de forms usando um MobPosition e MobDimension já instanciado.
* fica de responsabilidade de quem chamou a função liberar corretamente a memória de MobPosition e MobDimension
*
* position - objeto do tipo MobPosition
* dimension - objeto do tipo MobDimensions
*
* > o objeto instanciado
*/
MobFormChain* mob_form_create_chain_referenced(MobPosition*, MobDimension*);

/** libera a memória da lista, não libera memoria das dependencias
*
* self - objeto MobShapeChain.
*/
void mob_form_delete_chain(MobFormChain**);

/** libera a memória da lista e das dependencias
*
* self - objeto MobShapeChain.
*/
void mob_form_delete_chain_cascaded(MobFormChain**);

/** adiciona ao topo da lista
* 
* header - inicio da lista
* self - objeto MobShapeChain.
*/
void mob_form_add_to_chain(MobFormChain**, MobFormChain*);

/** remove do topo da lista
*
* header - inicio da lista
* self - objeto MobShapeChain.
*/
MobFormChain* mob_form_remove_top_chain(MobFormChain**);

/** remove o objeto especifo da lista
*
* header - inicio da lista
* self - objeto MobShapeChain.
*/
MobFormChain* mob_form_remove_reference_chain(MobFormChain**, MobFormChain*);

#ifdef __cplusplus
}
#endif

#endif //MOB_POSITION_HEADER_INCLUDED