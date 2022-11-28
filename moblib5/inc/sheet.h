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

#ifndef MOB_SHEET_HEADER_INCLUDED
#define MOB_SHEET_HEADER_INCLUDED

#include "types.h"
#include "position.h"

#ifdef __cplusplus
extern "C" {
#endif

/** estrutura para armazenar uma animação
*
* start - em qual celula a animação inicia
* end - em qual celula a animação termina
* index - posição atual da celula
* flip - usado esclusivamente para o modo MOB_ANIMATE_FLIP
* clock - temporizador para contar o delay entre as celulas
* info - informações em comum entre animações
*/
typedef struct _MobSheet {
	int totalCells, *cellX, *cellY;

	float handleX[9], handleY[9];

	// o tamanho de uma celula
	MobDimension cell_dimension;
	// a quantidade de celulas
	MobDimension sheet_dimension;
}MobSheet;

/** instancia o objeto MobSheet
*
* width - largura (em pixel) do sheet
* height - altura (em pixel) do sheet
* cols - colunas (em celulas)
* rows - linhas (em celulas)
*
* > o objeto instanciado
*/
MobSheet* mob_sheet_create(int, int, int, int);

/** destroi o objeto MobSheet
*
* self - o objeto a ser destruido
*/
void mob_sheet_delete(MobSheet*);

#ifdef __cplusplus
}
#endif

#endif //MOB_SHEET_HEADER_INCLUDED