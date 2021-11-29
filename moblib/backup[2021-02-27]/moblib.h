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

	#include "timing.h" // finalizada!
	#include "thread.h" // semi finalizado!
	#include "sheet.h" //finalizada!
	#include "animation.h" //finalizada
	#include "moviment.h" // finalizada!
	#include "colision.h" // em teste!
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
