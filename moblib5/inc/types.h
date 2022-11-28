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

#ifndef MOB_TYPES_HEADER_INCLUDED
#define MOB_TYPES_HEADER_INCLUDED

#include <stdint.h>

#ifndef __cplusplus

/** tipo de dado para representar um booleano
*/
typedef uint8_t bool;

/** flags para representar estado verdadeiro ou falso
*/
#define true 1
#define false 0

#endif

/** tipo de dado para encurtar definições de tipos numéricos
*/
typedef unsigned int uint;
typedef unsigned short int usint;
typedef unsigned long int ulint;
typedef unsigned long long int ullint;
typedef short int sint;
typedef long int lint;
typedef long long int llint;

/** tipos de dados para simbolizar posicionamento referente aos eixos
* para verificar se uma flag é vertical ou horizontal fazer and com a flag
* ex: if (my_flag_code & VERTICAL) printf("é vertical");
* pode-se usar duas flags simples para formar uma diagonal
* ex: (UP | LEFT == UP_LEFT)
* e pode-se usar flags simples para verificar se é vertical tambem
* ex: (my_flag_code & (UP | DOWN))
*/
#define UP         0b0001	 // cima
#define DOWN       0b0010    // baixo
#define LEFT       0b0100    // esquerda
#define RIGHT      0b1000    // direita

#define OUTER      0b0000    // fora
#define INNER      0b1111    // dentro

#define VERTICAL   0b0011    // vertical
#define HORIZONTAL 0b1100    // horizonal

#define UP_LEFT    0b0101    // cima e esquerda
#define UP_RIGHT   0b1001    // cima e direita
#define DOWN_LEFT  0b0110    // baixo e esquerda
#define DOWN_RIGHT 0b1010    // baixo e direita


#endif //MOB_TYPES_HEADER_INCLUDED