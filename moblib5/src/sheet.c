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

#ifndef MOB_SHEET_SOURCE_INCLUDED
#define MOB_SHEET_SOURCE_INCLUDED

#include <stdlib.h>
#include "../inc/types.h"
#include "../inc/safe.h"
#include "../inc/sheet.h"

#ifdef __cplusplus
extern "C" {
#endif


extern MobSheet* mob_sheet_create(int width, int height, int cols, int rows) {
	MobSheet* sheet = safe_calloc_this(struct _MobSheet);

	float w = sheet->cell_dimension.width =  (float)width / cols;
	float h = sheet->cell_dimension.height = (float)height / rows;
	sheet->sheet_dimension.width = (float)cols;
	sheet->sheet_dimension.height = (float)rows;
	sheet->totalCells = cols * rows;

	float hw = w / 2;
	float hh = h / 2;

	sheet->handleX[0] = 0;   sheet->handleY[0] = 0;
	sheet->handleX[1] = -hw; sheet->handleY[1] = 0;
	sheet->handleX[2] = -w;  sheet->handleY[2] = 0;
	sheet->handleX[3] = 0;   sheet->handleY[3] = -hh;
	sheet->handleX[4] = -hw; sheet->handleY[4] = -hh;
	sheet->handleX[5] = -w;  sheet->handleY[5] = -hh;
	sheet->handleX[6] = 0;   sheet->handleY[6] = -h;
	sheet->handleX[7] = -hw; sheet->handleY[7] = -h;
	sheet->handleX[8] = -w;  sheet->handleY[8] = -h;

	sheet->cellX = safe_calloc_these(int, sheet->totalCells);
	sheet->cellY = safe_calloc_these(int, sheet->totalCells);

	for (int index = 0; index < sheet->totalCells; index++) {
		sheet->cellX[index] = index % cols * (int)w;
		sheet->cellY[index] = (index / cols)* (int)h;
	}
	return sheet;
}


extern void mob_sheet_delete(MobSheet* self) {
	free(self->cellX);
	free(self->cellY);
	self->cellX = 0;
	self->cellY = 0;
}


#ifdef __cplusplus
}
#endif

#endif //MOB_SHEET_SOURCE_INCLUDED
