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

#ifndef MAP_H
#define MAP_H

#include "sheet.h"
#include "moviment.h"
#include "colision.h"
#include <iostream>
#include <fstream>
#define index(x, y, width) x+y*width

class MOB_MAP {
public:
	int width = 0, height = 0;
	int ***buffer = nullptr;
	int *mob_map_cell_size = nullptr;
	int **locals = nullptr;
	int localSize = 0;
		

	// <width, height>
	MOB_MAP(int w, int h) {
		this->width = w, this->height = h;

		buffer = (int***)calloc(sizeof(int**), w*h);
			

		mob_map_cell_size = (int*)calloc(sizeof(int), w*h);
			
		for (int i = 0;i < w*h;i++) mob_map_cell_size[i] = 0;
	}
	~MOB_MAP() {
		for (int i = 0;i < localSize && locals[i];i++) { free(locals[i]); }
		if(locals)free(locals);
		for (int i = 0;i < width * height && buffer[i];i++) { free(buffer[i]); }
		if(buffer)free(buffer);
	}
};

// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int x, int y, int val) {
	if (x >= self->width || y >= self->height)return false;
	self->buffer[index(x, y, self->width)] = (int**)realloc(self->buffer[index(x, y, self->width)], ++self->mob_map_cell_size[index(x, y, self->width)] * sizeof(int*));
	self->locals = (int**)realloc(self->locals, sizeof(int*)*++self->localSize);
	self->locals[self->localSize - 1] = (int*)malloc(sizeof(int));
	*self->locals[self->localSize - 1] = val;
	self->buffer[index(x, y, self->width)][self->mob_map_cell_size[index(x, y, self->width)] - 1] = self->locals[self->localSize - 1];
	return true;
}
// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int x, int y, int *val) {
	if (x >= self->width || y >= self->height)return false;
	self->buffer[index(x, y, self->width)] = (int**)realloc(self->buffer[index(x, y, self->width)], ++self->mob_map_cell_size[index(x, y, self->width)] * sizeof(int*));
	self->buffer[index(x, y, self->width)][self->mob_map_cell_size[index(x, y, self->width)] - 1] = val;
	return true;
}
// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int i, int val) {
	if (i >= self->width * self->height)return false;
	self->buffer[i] = (int**)realloc(self->buffer[i], ++self->mob_map_cell_size[i] * sizeof(int*));
	self->locals = (int**)realloc(self->locals, sizeof(int*)*++self->localSize);
	self->locals[self->localSize - 1] = (int*)malloc(sizeof(int));
	*self->locals[self->localSize - 1] = val;
	self->buffer[i][self->mob_map_cell_size[i] - 1] = self->locals[self->localSize - 1];
	return true;
}
// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int i, int *val) {
	if (i >= self->width * self->height)return false;
	self->buffer[i] = (int**)realloc(self->buffer[i], ++self->mob_map_cell_size[i] * sizeof(int*));
	self->buffer[i][self->mob_map_cell_size[i] - 1] = val;
	return true;
}

//retorna uma posicao no mapa, referente a sua camada 
int mob_map_cell(MOB_MAP *self, int x, int y, int l) {
	if (x >= self->width || y >= self->height || l >= self->mob_map_cell_size[index(x, y, self->width)]) { /* adicionar retorno de erro*/ return -1; }
	return *self->buffer[index(x, y, self->width)][l];
}

//retorna uma posicao no mapa, referente a sua camada 
int mob_map_cell(MOB_MAP *self, int i, int l) {
	//if (i >= self->width * self->height && l >= self->mob_map_cell_size[i]) { /* adicionar retorno de erro*/ return -1; }
	return *self->buffer[i][l];
}

// modifica uma posicao no mapa
void mob_map_modifier(MOB_MAP *self, int x, int y, int l, int val) {
	//if (x >= self->width || y >= self->height || l >= self->mob_map_cell_size[index(x, y, self->width)]) { /* adicionar retorno de erro*/ }
	*self->buffer[index(x, y, self->width)][l] = val;
}

// modifica uma posicao no mapa
void mob_map_modifier(MOB_MAP *self, int i, int l, int val) {
	//if (i >= self->width * self->height && l >= self->mob_map_cell_size[i]) { /* adicionar retorno de erro*/ }
	*self->buffer[i][l] = val;
}

int mob_map_cell_size(MOB_MAP *self, int x, int y) { // retorna quantos camadas tem a posicao no mapa
	if (x >= self->width || y >= self->height) { /* adicionar retorno de erro*/ return -1; }
	return self->mob_map_cell_size[index(x, y, self->width)];
}
int mob_map_cell_size(MOB_MAP *self, int i) { // retorna quantos camadas tem a posicao no mapa
	if (i >= self->width * self->height) { /* adicionar retorno de erro*/ return -1; }
	return self->mob_map_cell_size[i];
}



class MOB_MAPPING {
public:
	int limiter_x, limiter_y, limiter_w, limiter_h;
	bool local_map = true;
	MOB_MAP *map = nullptr;

	// <width, height, draw limiter:[x, y, width, height]>
	MOB_MAPPING(int width, int height, int limiter_x = 0, int limiter_y = 0, unsigned short int limiter_w = -1, unsigned short int limiter_h = -1) {
		this->map = new MOB_MAP(width, height);
		limiter_x = limiter_x, limiter_y = limiter_y, limiter_w = limiter_w, limiter_h = limiter_h;
	}

	MOB_MAPPING() {}

	// desaloca a memoria
	~MOB_MAPPING() { if (local_map) free(map); }
};

//sobrescreve o mapa
void mob_overwrite_map(MOB_MAPPING* self, MOB_MAP* map) { if (self->local_map) { free(self->map); self->local_map = false; } self->map = map; }
//sobrescreve o mapa
void mob_overwrite_map(MOB_MAPPING* self, MOB_MAP map) { if (self->local_map) { free(self->map); } self->local_map = true; self->map = new MOB_MAP(map); }

// retorna true se esta fora do limite de desenho
inline int mob_overdraw(MOB_MAPPING* map, MOB_MOVIMENT::INSTANCE* self, MOB_SHEET *MOB_SHEET, int x, int y) {
	return (self->x + x * MOB_SHEET->cellWidth + MOB_SHEET->cellWidth  < map->limiter_x ||
		self->y + y * MOB_SHEET->cellHeight + MOB_SHEET->cellHeight < map->limiter_y ||
		self->x + x * MOB_SHEET->cellWidth  > map->limiter_w ||
		self->y + y * MOB_SHEET->cellHeight > map->limiter_h);
}
// retorna o a posicao X  no spritesheet
inline int mob_map_tile_x(MOB_MAPPING* self, MOB_SHEET *MOB_SHEET, int x, int y, int i = 0) { return MOB_SHEET->cellX[mob_map_cell(self->map, x, y, i)]; }

// retorna o a posicao Y  no spritesheet
inline int mob_map_tile_y(MOB_MAPPING* self, MOB_SHEET *MOB_SHEET, int x, int y, int i = 0) { return MOB_SHEET->cellY[mob_map_cell(self->map, x, y, i)]; }

// retorna a posicao X na tela
inline float mob_map_position_x(MOB_MOVIMENT::INSTANCE* self, MOB_SHEET *MOB_SHEET, int x, int y) { return self->x + x * MOB_SHEET->cellWidth; }

// retorna a posicao Y na tela
inline float mob_map_position_y(MOB_MOVIMENT::INSTANCE* self, MOB_SHEET *MOB_SHEET, int x, int y) { return self->y + y * MOB_SHEET->cellHeight; }


// carrega o mapa de uma data para um buffer temporario limpo.
void mob_load_map(MOB_MAPPING* self, std::string name) {

	

	std::ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {// pega a largura e altura do mapa
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
	MOB_MAP *tmp = new MOB_MAP(width, height);// cria um novo mapa
	int i = 0;
	while (file.get(var)) {// adiciona as chaves ao mapa

		if (var != '\n') {
			conv = var - 48;
			mob_map_add(tmp, i, conv);
			i++;
		}
	}

	mob_overwrite_map(self, tmp);// sobrescreve o mapa de origem
	self->local_map = true;
}

// carrega uma camada de uma data para um buffer temporario ja iniciado.
void mob_load_map_layer(MOB_MAPPING* self, std::string name) {

	std::ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {// pega a largura e altura do mapa
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
	while (file.get(var)) { // adiciona as chaves ao mapa

		if (var != '\n') {
			conv = var - 48;
			mob_map_add(self->map, i, conv);
			i++;
		}
	}


	self->local_map = true;
}

// nao testado
void mob_load_map_animation_layer(MOB_MAPPING* self, MOB_ANIM::ANIMATE* mob_anim, char key,  std::string name) {
	
	std::ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {// pega a largura e altura do mapa
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

	for (int i = 0; i < width * height; i++) { // adiciona as chaves ao mapa
		file.get(var);
		if (var == key) {
			mob_map_add(self->map, i, &mob_anim->index);
		}
	}

	self->local_map = false;
}

#endif