#ifndef _SYS_PLAYER_H
#define _SYS_PLAYER_H

#include "moblib/moblib.h"

class switchAnimation {
public:
	int anim = 0;
	int anim_pos = 0;
};

class shoot_atack {
public:
	MOVIMENT::AUTO<MOVIMENT::INSTANCE> *bullet;
	COLLISION::COLID *bulletform;
	COLLISION::COLID *targetform;
	template <class T>
	shoot_atack(OBJECT<T>* player, MOVIMENT::INSTANCE* target, SHEET* targetSht) {
		bullet = (new MOVIMENT::AUTO<MOVIMENT::INSTANCE>(new MOVIMENT::INSTANCE(player->moviment->pos->x, player->moviment->pos->y)));
		bulletform = new MOVIMENT::FORM(bullet->pos,5,5);
		targetform = new MOVIMENT::FORM(target, targetSht);
	}
	~shoot_atack() {
		delete bullet;
		delete bulletform;
		delete targetform;
	}
};

template <class T>
void attack(OBJECT<T>* player, MOVIMENT::INSTANCE *target, SHEET* targetSht, CHANNELS* tr_queue) {
	addthread(tr_queue, iniTHREAD(new shoot_atack(player, target, targetSht), 22));
}

void gravit(MOVIMENT::INSTANCE *self,int power) {
	self->y -= power;
}

template <class T>
void switchPlayerAnimation(OBJECT<T>* player, switchAnimation* pos) {
	switch (player->moviment->dirMiddle) {
	case MOVIMENT::UP:
		pos->anim = 3;
		if (player->moviment->UP) {

			ANIM::anim(player->animation[pos->anim]);
			pos->anim_pos = player->animation[pos->anim]->index;
		}
		else {
			pos->anim_pos = 37;
			pos->anim_pos = player->animation[pos->anim]->start + 1;
		}
		break;
	case MOVIMENT::LEFT:
	case MOVIMENT::DOWN_LEFT:
	case MOVIMENT::UP_LEFT:
		pos->anim = 1;
		if (player->moviment->LEFT) {
			ANIM::anim(player->animation[pos->anim]);
			pos->anim_pos = player->animation[pos->anim]->index;
		}
		else {
			pos->anim_pos = 13;
			pos->anim_pos = player->animation[pos->anim]->start + 1;
		}
		break;
	case MOVIMENT::DOWN:
		pos->anim = 0;
		if (player->moviment->DOWN) {

			ANIM::anim(player->animation[pos->anim]);
			pos->anim_pos = player->animation[pos->anim]->index;
		}
		else {
			pos->anim_pos = 1;
			pos->anim_pos = player->animation[pos->anim]->start + 1;
		}
		break;
	case MOVIMENT::RIGHT:
	case MOVIMENT::DOWN_RIGHT:
	case MOVIMENT::UP_RIGHT:
		pos->anim = 2;
		if (player->moviment->RIGHT) {

			ANIM::anim(player->animation[pos->anim]);
			pos->anim_pos = player->animation[pos->anim]->index;
		}
		else {
			pos->anim_pos = 25;
			pos->anim_pos = player->animation[pos->anim]->start + 1;
		}
		break;
	}
}

#endif
