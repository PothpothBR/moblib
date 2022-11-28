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

#ifndef MOB_SAFE_SOURCE_INCLUDED
#define MOB_SAFE_SOURCE_INCLUDED

#include "../inc/types.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


extern void* safe_calloc(uint type, uint size) {
	void* res = calloc(type, size);
	if (!res) {
		printf("falha ao alocar memoria! <function safe_calloc(%u, %u)>", type, size);
		exit(-1);
	};
	return res;
}


extern void* safe_realloc(void* ponter, uint size, uint type) {
	void* res = realloc(ponter, size * type);
	if (!res) {
		printf("falha ao alocar memoria! <function safe_realloc(%u, %u)>", size, type);
		exit(-1);
	};
	return res;
}


#ifdef __cplusplus
}
#endif

#endif //MOB_SAFE_SOURCE_INCLUDED