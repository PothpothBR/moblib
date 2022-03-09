/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     /  _|             |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/
#ifndef MOBLIB_H
#define MOBLIB_H

	// modificar os contrutores das clases para serem externos
	//pelo fato de que construtuores internos que alocam ponteiros para o heap tendem a falhar quando definidos como vetores ou matrizes
	// por que ao tentar construir a classe com uma copia dela mesma "class[0] = class()" tudo oque nao for alocado localmente sera perdido
#include "position.h" // finalizado!
#include "timing.h" // finalizada!
#include "thread.h" // semi finalizado!
#include "sheet.h" // finalizada!
#include "animation.h" //finalizada
#include "moviment.h" // finalizada!
#include "colision.h" // finalizada!
#include "mapping.h" // finalizado!
	
	// retorna o fps em milisegundos
#define FPS_TO_SEC(fps) 1/fps
	// retorna quantos frames sao nescessarios para decorrer um certo tempo
#define SEC_to_FPS(sec, fps) sec/FPS_TO_SEC(fps)
	// retorna o maior
#define BIGGER(a, b) (a > b) ? a : b
	// retorna o menor
#define SMALLER(a, b) (a < b) ? a : b
	// aredonda para cima
#define ROUNDUP(a) (int)a+a%1
	
#endif
