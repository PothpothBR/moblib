#ifndef _SYS_CORE_H
#define _SYS_CORE_H

#include "moblib/moblib.h"
#include "_characters.h"
#include <fstream>
#include <string>

constexpr float FPS = 0.025;

CHANNELS *channel;// cria o canal de threads
MOVIMENT::MOUSE<MOVIMENT::INSTANCE> *mouse;// cria o objeto mouse
COLLISION::COLID *_mouse;// cria o colisor do mouse
OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>> *player;// cria o objeto player
switchAnimation *pswitch;// cria a animacao do player
OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>> *map;// cria o mapa

COLLISION::COLID *test;
OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>> *player1;


class _routines {
public:

	_routines() {
		
		test = new COLLISION::COLID(new float(500), new float(500), 150, 1);
		player1 = new OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>>(0);
		player1->moviment = new MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(200, 200), 72);
		player1->format = new COLLISION::COLID(&player1->moviment->pos->x, &player1->moviment->pos->y, 50, 50);

		channel = new CHANNELS;// instanciar o canal de threads
		addchanel(channel, 22, 0.5, FPS);// cria um canal com ID = 22

		
		mouse = new MOVIMENT::MOUSE<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(200, 200));// instanciar mouse...
		_mouse = new COLLISION::COLID(&mouse->pos->x,&mouse->pos->y,1, 1);// instancia o colisor do mouse

		// instanciar objeto player
		player = new OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>>(4);
		player->instance = new ANIM::INSTANCE(3, ANIM::FLIP, 0.2, FPS);               // personagem 
		for (int i = 0;i < 4;i++)player->animation[i] = new ANIM::ANIMATE(player->instance, i * 12 + 3 * 2);
		player->sheet = new SHEET(576, 576, 12, 8);
		player->moviment = new MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(1080/2-player->sheet->cellWidth, 720/2-player->sheet->cellHeight),0);
		player->format = new COLLISION::COLID(&player->moviment->pos->x, &player->moviment->pos->y, player->sheet->cellWidth, player->sheet->cellHeight);
		pswitch = new switchAnimation();
		// -----------------------

		// instanciar objeto mapa
		map = new OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>>(1);
		map->instance = new ANIM::INSTANCE(4, ANIM::FORWARD);
		map->animation[0] = new ANIM::ANIMATE(map->instance, 0);
		map->moviment = new MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(0, 0), 8);
		map->sheet = new SHEET(128, 32, 4, 1);
		map->mapping = new MAPPING(0, 0, 0, 0, 1080, 720);
		map->format = new COLLISION::COLID(&map->moviment->pos->x, &map->moviment->pos->y, map->sheet->cellWidth, map->sheet->cellHeight);
		// -----------------------


		loadmap(map->mapping, "map.mdt");// carrega o mapa
		loadmaplayer(map->mapping, "mapcolid.mdt");// carrega a camada de colisao
 
	}

	~_routines() {
		// removendo o ponteiro de map::moviment pois o mesmo é erdado de player::moviment
		map->moviment = nullptr;
		// deletar dados do sys
		delete channel;
		delete map;
		delete player;
		delete mouse;
		delete _mouse;
		//  -------------------
	}

}Sys;

void manipQueue(CHANNELS* channel) { // roda ao mespo tempo de execussao do loop principal
	int indx = channel->getChanelById(22);// pega a posicao do canal
	THREAD *get = channel->head[indx]; // pega o thread head
	for (int i = 0;i < channel->size[indx];i++) {
			
		ranged_atack *tmp = (ranged_atack*)get->obj;// cria um manipulado especifico para a classe do thread

		// aqui vai a execusao referente ao thread <tmp><id = 32>
        MOVIMENT::direction(tmp->bullet, *tmp->targetform->x, *tmp->targetform->y, 12);
		MOVIMENT::run(tmp->bullet);
		// ------------------------------------------------------

		// aqui remove o thread se nessesario
		get = get->next;
		if (COLLISION::collision(tmp->bulletform,tmp->targetform))remthread(channel,22,i);
		// ----------------------------------
	}

}

#endif