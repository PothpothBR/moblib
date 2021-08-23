#ifndef _SYS_CORE_H
#define _SYS_CORE_H

#include "moblib/moblib.h"
#include "_characters.h"
#include <fstream>
#include <string>

constexpr float FPS = 0.025;

CHANNELS *channel;
MOVIMENT::MOUSE<MOVIMENT::INSTANCE> *mouse;
COLLISION::COLID *_mouse;
OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>> *player1;
switchAnimation *p1switch;
OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>> *player;
switchAnimation *pswitch;
OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>> *map;

void loadmap(MAPPING* self, string name);
void loadmaplayer(MAPPING* self, string name);

class _routines {
public:

	_routines() {
		// instanciar o canal de threads
		channel = new CHANNELS;
		addchanel(channel, 22, 0.5, FPS);

		// instanciar mouse...
		mouse = new MOVIMENT::MOUSE<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(200, 200));
		_mouse = new COLLISION::COLID(&mouse->pos->x,&mouse->pos->y,1, 1);

		// instanciar objeto player
		player = new OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>>(4);
		player->instance = new ANIM::INSTANCE(3, ANIM::FLIP, 0.2, FPS);               // personagem 
		for (int i = 0;i < 4;i++)player->animation[i] = new ANIM::ANIMATE(player->instance, i * 12 + 3 * 2);
		player->sheet = new SHEET(576, 576, 12, 8);
		player->moviment = new MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(1080/2-player->sheet->cellWidth, 720/2-player->sheet->cellHeight),0);
		player->format = new COLLISION::COLID(&player->moviment->pos->x, &player->moviment->pos->y, player->sheet->cellWidth, player->sheet->cellHeight);
		pswitch = new switchAnimation();

		// instanciar objeto mapa
		map = new OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>>(1);
		map->instance = new ANIM::INSTANCE(4, ANIM::FORWARD);
		map->animation[0] = new ANIM::ANIMATE(map->instance, 0);
		map->moviment = new MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(0, 0), 8);
		map->sheet = new SHEET(128, 32, 4, 1);
		map->mapping = new MAPPING(0, 0, 0, 0, 1080, 720);
		map->format = new COLLISION::COLID(&map->moviment->pos->x, &map->moviment->pos->y, map->sheet->cellWidth, map->sheet->cellHeight);

		// instanciar objeto player
		player1 = new OBJECT<MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>>(4);
		player1->instance = new ANIM::INSTANCE(3, ANIM::FLIP, 0.2, FPS);               // personagem 
		for (int i = 0;i < 4;i++)player1->animation[i] = new ANIM::ANIMATE(player1->instance, i * 12 + 3 * 3);
		player1->moviment = new MOVIMENT::KEYBOARD<MOVIMENT::INSTANCE>(map->moviment->pos, 2);
		player1->sheet = new SHEET(576, 576, 12, 8);
		player1->format = new COLLISION::COLID(&player1->moviment->pos->x, &player1->moviment->pos->y, player1->sheet->cellWidth, player1->sheet->cellHeight);
		p1switch = new switchAnimation();

		
		

		loadmap(map->mapping, "map.mdt");
		loadmaplayer(map->mapping, "mapcolid.mdt");
 
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
	}

}Sys;

void loadmap(MAPPING* self,string name) {

	ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {
		if (var != '\n') {
			width++;
		}
		else {
			height++;
		}
	}

	width /= height+1;

	file.close();
	file.open(name);

	int conv;
	MAP *tmp = new MAP(width,height);
	int i = 0;
	while (file.get(var)) {

		if (var != '\n') {
			conv = var - 48;
			add(tmp, i, conv);
			i++;
		}
	}

	overwriteMap(self, tmp);
	self->localMap = true;
}

void loadmaplayer(MAPPING* self, string name) {

	ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {
		if (var != '\n') {
			width++;
		}
		else {
			height++;
		}
	}

	width /= height + 1;

	file.close();
	file.open(name);

	int conv;
	int i = 0;
	while (file.get(var)) {

		if (var != '\n') {
			conv = var - 48;
			add(self->map, i, conv);
			i++;
		}
	}

	
	self->localMap = true;
}

void manipQueue(CHANNELS* channel) { // roda ao mespo tempo de execussao do loop principal
	int indx = channel->getChanelById(22);
	THREAD *get = channel->head[indx];
	for (int i = 0;i < channel->size[indx];i++) {
			
		shoot_atack *tmp = (shoot_atack*)get->obj;
		// aqui vai a execusao referente ao thread <tmp><id = 32>
        MOVIMENT::direction(tmp->bullet, *tmp->targetform->x, *tmp->targetform->y, 12);
		MOVIMENT::run(tmp->bullet);
		// ----------------------------------------
		// aqui remove o thread se nessesario
		get = get->next;
		if (COLLISION::collision(tmp->bulletform,tmp->targetform))remthread(channel,22,i);
	}

}

#endif