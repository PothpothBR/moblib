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

#ifndef MOB_SAFE_HEADER_INCLUDED
#define MOB_SAFE_HEADER_INCLUDED

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** um alias amigavel para alocar memoria para um objeto unico
*
* type - o objeto em si. (ex. int x = safe_calloc_one(int))
*
* > a memoria alocada se suceso, caso contrario imprime um erro e para o programa
*/
#define safe_calloc_this(_Type) (_Type*)safe_calloc(sizeof(_Type), 1)

/** um alias amigavel para alocar memoria para um vetor de objetos 
*
* type - o objeto em si. (ex. int x = safe_calloc_all(int, 22))
* size - quantidade de objetos a serem alocados
*
* > a memoria alocada se suceso, caso contrario imprime um erro e para o programa
*/
#define safe_calloc_these(_Type, size) (_Type*)safe_calloc(sizeof(_Type), size)

/** sobrecarrega calloc com verificação de falha na alocação
*
* type - tamanho do objeto a ser alocado
* size - quantidade de objetos a serem alocados
*
* > a memoria alocada se suceso, caso contrario imprime um erro e para o programa
*/
void* safe_calloc(uint, uint);

#ifdef __cplusplus
}
#endif

#endif //MOB_SAFE_HEADER_INCLUDED
