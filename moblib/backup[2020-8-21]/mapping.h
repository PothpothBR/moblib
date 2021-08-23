#ifndef MAP_H
#define MAP_H

#include "sheet.h"
#include "moviment.h"
#include <iostream>
#include <fstream>
#define index(x, y, width) x+y*width

class MAP {
public:
	int width = 0, height = 0;
	int ***buffer = nullptr;
	int *cellSize = nullptr;
	int **locals = nullptr;
	int localSize = 0;
		

	// <width, height>
	MAP(int w, int h) {
		this->width = w, this->height = h;

		buffer = (int***)calloc(sizeof(int**), w*h);
			

		cellSize = (int*)calloc(sizeof(int), w*h);
			
		for (int i = 0;i < w*h;i++) cellSize[i] = 0;
	}
	~MAP() {
		for (int i = 0;i < localSize && locals[i];i++) { free(locals[i]); }
		if(locals)free(locals);
		for (int i = 0;i < width * height && buffer[i];i++) { free(buffer[i]); }
		if(buffer)free(buffer);
	}
};

// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool add(MAP *self, int x, int y, int val) {
	if (x >= self->width || y >= self->height)return false;
	self->buffer[index(x, y, self->width)] = (int**)realloc(self->buffer[index(x, y, self->width)], ++self->cellSize[index(x, y, self->width)] * sizeof(int*));
	self->locals = (int**)realloc(self->locals, sizeof(int*)*++self->localSize);
	self->locals[self->localSize - 1] = (int*)malloc(sizeof(int));
	*self->locals[self->localSize - 1] = val;
	self->buffer[index(x, y, self->width)][self->cellSize[index(x, y, self->width)] - 1] = self->locals[self->localSize - 1];
	return true;
}
// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool add(MAP *self, int x, int y, int *val) {
	if (x >= self->width || y >= self->height)return false;
	self->buffer[index(x, y, self->width)] = (int**)realloc(self->buffer[index(x, y, self->width)], ++self->cellSize[index(x, y, self->width)] * sizeof(int*));
	self->buffer[index(x, y, self->width)][self->cellSize[index(x, y, self->width)] - 1] = val;
	return true;
}
// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool add(MAP *self, int i, int val) {
	if (i >= self->width * self->height)return false;
	self->buffer[i] = (int**)realloc(self->buffer[i], ++self->cellSize[i] * sizeof(int*));
	self->locals = (int**)realloc(self->locals, sizeof(int*)*++self->localSize);
	self->locals[self->localSize - 1] = (int*)malloc(sizeof(int));
	*self->locals[self->localSize - 1] = val;
	self->buffer[i][self->cellSize[i] - 1] = self->locals[self->localSize - 1];
	return true;
}
// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool add(MAP *self, int i, int *val) {
	if (i >= self->width * self->height)return false;
	self->buffer[i] = (int**)realloc(self->buffer[i], ++self->cellSize[i] * sizeof(int*));
	self->buffer[i][self->cellSize[i] - 1] = val;
	return true;
}

//retorna uma posicao no mapa, referente a sua camada 
int cell(MAP *self, int x, int y, int l) {
	if (x >= self->width || y >= self->height || l >= self->cellSize[index(x, y, self->width)]) { /* adicionar retorno de erro*/ return -1; }
	return *self->buffer[index(x, y, self->width)][l];
}

//retorna uma posicao no mapa, referente a sua camada 
int cell(MAP *self, int i, int l) {
	if (i >= self->width * self->height && l >= self->cellSize[i]) { /* adicionar retorno de erro*/ return -1; }
	return *self->buffer[i][l];
}

int& mod(MAP *self, int x, int y, int l) {
	if (x >= self->width || y >= self->height || l >= self->cellSize[index(x, y, self->width)]) { /* adicionar retorno de erro*/ }
	return *self->buffer[index(x, y, self->width)][l];
}

int& mod(MAP *self, int i, int l) {
	if (i >= self->width * self->height && l >= self->cellSize[i]) { /* adicionar retorno de erro*/ }
	return *self->buffer[i][l];
}

int cellSize(MAP *self, int x, int y) { // retorna quantos camadas tem a posicao no mapa
	if (x >= self->width || y >= self->height) { /* adicionar retorno de erro*/ return -1; }
	return self->cellSize[index(x, y, self->width)];
}
int cellSize(MAP *self, int i) { // retorna quantos camadas tem a posicao no mapa
	if (i >= self->width * self->height) { /* adicionar retorno de erro*/ return -1; }
	return self->cellSize[i];
}



class MAPPING {
public:
	int lx, ly, lw, lh;
	bool localMap = true;
	MAP *map = nullptr;

	// <width, height, draw limiter:[x, y, width, height]>
	MAPPING(int width, int height, int limiter_x = 0, int limiter_y = 0, unsigned short int limiter_w = -1, unsigned short int limiter_h = -1) {
		this->map = new MAP(width, height);
		lx = limiter_x, ly = limiter_y, lw = limiter_w, lh = limiter_h;
	}
	// desaloca a memoria
	~MAPPING() { if (localMap) free(map); }
};

//sobrescreve o mapa
void overwriteMap(MAPPING* self, MAP* map) { if (self->localMap) { free(self->map); self->localMap = false; } self->map = map; }
//sobrescreve o mapa
void overwriteMap(MAPPING* self, MAP map) { if (self->localMap) { free(self->map); } self->localMap = true; self->map = new MAP(map); }

// retorna true se esta fora do limite de desenho
inline int overdraw(MAPPING* map, MOVIMENT::INSTANCE* self, SHEET *sheet, int x, int y) {
	return (self->x + x * sheet->cellWidth + sheet->cellWidth  < map->lx ||
		self->y + y * sheet->cellHeight + sheet->cellHeight < map->ly ||
		self->x + x * sheet->cellWidth  > map->lx + map->lw ||
		self->y + y * sheet->cellHeight > map->ly + map->lh);
}
// retorna a posicao X  no spritesheet
inline int tileX(MAPPING* self, SHEET *sheet, int x, int y, int i = 0) { return sheet->cellX[cell(self->map, x, y, i)]; }
// retorna a posicao Y  no spritesheet
inline int tileY(MAPPING* self, SHEET *sheet, int x, int y, int i = 0) { return sheet->cellY[cell(self->map, x, y, i)]; }
// retorna a posicao X na tela
inline float mapX(MOVIMENT::INSTANCE* self, SHEET *sheet, int x, int y) { return self->x + x * sheet->cellWidth; }
// retorna a posicao Y na tela
inline float mapY(MOVIMENT::INSTANCE* self, SHEET *sheet, int x, int y) { return self->y + y * sheet->cellHeight; }

// carrega o mapa de uma data para um buffer temporario limpo.
void loadmap(MAPPING* self, std::string name) {

	

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
	MAP *tmp = new MAP(width, height);// cria um novo mapa
	int i = 0;
	while (file.get(var)) {// adiciona as chaves ao mapa

		if (var != '\n') {
			conv = var - 48;
			add(tmp, i, conv);
			i++;
		}
	}

	overwriteMap(self, tmp);// sobrescreve o mapa de origem
	self->localMap = true;
}

// carrega uma camada de uma data para um buffer temporario ja iniciado.
void loadmaplayer(MAPPING* self, std::string name) {

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
			add(self->map, i, conv);
			i++;
		}
	}


	self->localMap = true;
}

#endif