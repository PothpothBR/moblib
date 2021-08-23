#pragma once
#include "moblib/moblib.h"
#include "deque"


class _player {
public:
	mlObject<mlMovimentKeys> Player;
	mlMovimentInstance mouse;
	bool mouse_is_pressed = false;

	int player_anim_pos = 0;
	int player_anim = 0;
	deque<mlMovimentAuto> rangedAttack;

	_player() {

		mouse.x = 0;
		mouse.y = 0;

		Player.animSize = 4;

		Player.sheet = initSheet(576, 576, 12, 8);
		Player.animInstance = initAnimationInstance(3, mlANIM_L, 16);
		Player.animation = initAnimation(&Player.animSize);

		Player.animation[3] = setAnimation(Player.animInstance, 0);
		Player.animation[2] = setAnimation(Player.animInstance, 12);
		Player.animation[1] = setAnimation(Player.animInstance, 24);
		Player.animation[0] = setAnimation(Player.animInstance, 36);

		Player.moviment = initMoviment<mlMovimentKeys>(600, 600, 8);


		Player.format = initFormat<mlMovimentKeys>(Player.moviment, Player.sheet);
	}

	void attack(mlFormat *target) {
		rangedAttack.emplace_back(mlMovimentAuto(Player.moviment->x, Player.moviment->y));
		mlDirection(&rangedAttack.back(), *target->x, *target->y, 12);

	}

	void switchAnimation() {
		switch (Player.moviment->dirMiddle) {
		case mlUP:
			if (Player.moviment->activeUP) {
				player_anim = 0;
				mlAnim(Player.animation[player_anim]);
				player_anim_pos = Player.animation[player_anim]->index;
			}
			else {
				player_anim_pos = 37;
			}
			break;
		case mlLEFT:
		case mlDOWN_LEFT:
		case mlUP_LEFT:
			if (Player.moviment->activeLEFT) {
				player_anim = 2;
				mlAnim(Player.animation[player_anim]);
				player_anim_pos = Player.animation[player_anim]->index;
			}
			else {
				player_anim_pos = 13;
			}
			break;
		case mlDOWN:
			if (Player.moviment->activeDOWN) {
				player_anim = 3;
				mlAnim(Player.animation[player_anim]);
				player_anim_pos = Player.animation[player_anim]->index;
			}
			else {
				player_anim_pos = 1;
			}
			break;
		case mlRIGHT:
		case mlDOWN_RIGHT:
		case mlUP_RIGHT:
			if (Player.moviment->activeRIGHT) {
				player_anim = 1;
				mlAnim(Player.animation[player_anim]);
				player_anim_pos = Player.animation[player_anim]->index;
			}
			else {
				player_anim_pos = 25;
			}
			break;
		}
	}

};