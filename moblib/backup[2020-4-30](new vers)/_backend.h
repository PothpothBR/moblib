#pragma once

#include "_player.h"

class _mobs {

};

class _npcs {

};

class _map {

};

class _pickable {

};

// para partes matematicas e lógicas
class _backEnd {
public:

	_player player;
	_npcs npcs;
	_mobs mobs;
	_pickable pickable;
	_map map;

	_backEnd() {

	}

	~_backEnd() {

	}
};