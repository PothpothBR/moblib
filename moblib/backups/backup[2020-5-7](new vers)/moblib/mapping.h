#ifndef MAP_H
#define MAP_H

#include "sheet.h"
#include "moviment.h"
//#include <deque>
#define index(x, y, width) x+y*width

typedef short int sint;

namespace MAP {
	class MAP {
	public:
		sint width = 0, height = 0;
		sint ***buffer = nullptr;
		sint *cellSize = nullptr;
		sint **locals = nullptr;
		sint localSize = 0;


		// <width, height>
		MAP(sint w, sint h) {
			this->width = w, this->height = h;

			buffer = (sint***)calloc(sizeof(sint**), w*h);

			cellSize = (sint*)calloc(sizeof(sint), w*h);
			for (int i = 0;i < w*h;i++) {
				cellSize = (sint*)calloc(sizeof(sint), w*h);
				cellSize[i] = 0;
			}
		}
		~MAP() {
			for (int i = 0;i < localSize;i++) { free(locals[i]); }
			free(locals);
			for (int i = 0;i < width * height;i++) { free(buffer[i]); }
			free(buffer);
		}
	};

	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool add(MAP *self, sint x, sint y, int val) {
		if (x >= self->width || y >= self->height)return false;
		self->buffer[index(x, y, self->width)] = (sint**)realloc(self->buffer[index(x, y, self->width)], ++self->cellSize[index(x, y, self->width)] * sizeof(sint*));
		self->locals = (sint**)realloc(self->locals, sizeof(sint*)*++self->localSize);
		self->locals[self->localSize - 1] = (sint*)malloc(sizeof(sint));
		*self->locals[self->localSize - 1] = val;
		self->buffer[index(x, y, self->width)][self->cellSize[index(x, y, self->width)] - 1] = self->locals[self->localSize - 1];
		return true;
	}
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool add(MAP *self, sint x, sint y, sint *val) {
		if (x >= self->width || y >= self->height)return false;
		self->buffer[index(x, y, self->width)] = (sint**)realloc(self->buffer[index(x, y, self->width)], ++self->cellSize[index(x, y, self->width)] * sizeof(sint*));
		self->buffer[index(x, y, self->width)][self->cellSize[index(x, y, self->width)] - 1] = val;
		return true;
	}
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool add(MAP *self, sint i, int val) {
		if (i >= self->width * self->height)return false;
		self->buffer[i] = (sint**)realloc(self->buffer[i], ++self->cellSize[i] * sizeof(sint*));
		self->locals = (sint**)realloc(self->locals, sizeof(sint*)*++self->localSize);
		self->locals[self->localSize - 1] = (sint*)malloc(sizeof(sint));
		*self->locals[self->localSize - 1] = val;
		self->buffer[i][self->cellSize[i] - 1] = self->locals[self->localSize - 1];
		return true;
	}
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool add(MAP *self, sint i, sint *val) {
		if (i >= self->width * self->height)return false;
		self->buffer[i] = (sint**)realloc(self->buffer[i], ++self->cellSize[i] * sizeof(sint*));
		self->buffer[i][self->cellSize[i] - 1] = val;
		return true;
	}

	//retorna uma posicao no mapa, referente a sua camada 
	sint cell(MAP *self, sint x, sint y, sint l) {
		if (x >= self->width || y >= self->height && l >= self->cellSize[index(x, y, self->width)]) { debugLog("error at get get - x:", x, "y:", y); return -1; }
		return *self->buffer[index(x, y, self->width)][l];
	}
	//retorna uma posicao no mapa, referente a sua camada 
	sint cell(MAP *self, sint i, sint l) {
		if (i >= self->width * self->height && l >= self->cellSize[i]) { debugLog("error at get get - index:", i); return -1; }
		return *self->buffer[i][l];
	}

	sint cellSize(MAP *self, sint x, sint y) { // retorna quantos camadas tem a posicao no mapa
		if (x >= self->width || y >= self->height) { debugLog("error at get buffer size - x:", x, "y:", y); return -1; }
		return self->cellSize[index(x, y, self->width)];
	}
	sint cellSize(MAP *self, sint i) { // retorna quantos camadas tem a posicao no mapa
		if (i >= self->width * self->height) { debugLog("error at get buffer size - index", i); return -1; }
		return self->cellSize[i];
	}



	class MAPPING {
	public:
		sint lx, ly, lw, lh;
		bool localMap = true;
		MAP *map = nullptr;

		// <width, height, draw limiter:[x, y, width, height]>
		MAPPING(sint width, sint height, sint limiter_x = 0, sint limiter_y = 0, unsigned short int limiter_w = -1, unsigned short int limiter_h = -1) {
			this->map = new MAP(width, height);
			lx = limiter_x, ly = limiter_y, lw = limiter_w, lh = limiter_h;
		}
		// desaloca a memoria
		~MAPPING() { if (localMap) free(map); }
	};

	//sobrescreve o mapa
	void overwriteMap(MAPPING* self, MAP* map) { if (self->localMap) { free(self->map); self->localMap = false; } self->map = map; }
	//sobrescreve o mapa
	void overwriteMap(MAPPING* self, MAP map) { if (self->localMap) { free(self->map); } self->map = new MAP(map); }

	// retorna true se esta fora do limite de desenho
	inline sint overdraw(MAPPING* map, MOVIMENT::INSTANCE* self, SHEET *sheet, sint x, sint y) {
		return (self->x + x * sheet->cellWidth + sheet->cellWidth  < map->lx ||
			self->y + y * sheet->cellHeight + sheet->cellHeight < map->ly ||
			self->x + x * sheet->cellWidth  > map->lx + map->lw ||
			self->y + y * sheet->cellHeight > map->ly + map->lh);
	}
	// retorna a posicao X  no spritesheet
	inline sint tileX(MAPPING* self, SHEET *sheet, sint x, sint y, sint i = 0) { return sheet->cellX[cell(self->map, x, y, i)]; }
	// retorna a posicao Y  no spritesheet
	inline sint tileY(MAPPING* self, SHEET *sheet, sint x, sint y, sint i = 0) { return sheet->cellY[cell(self->map, x, y, i)]; }
	// retorna a posicao X na tela
	inline sint mapX(MOVIMENT::INSTANCE* self, SHEET *sheet, sint x, sint y) { return self->x + x * sheet->cellWidth; }
	// retorna a posicao Y na tela
	inline sint mapY(MOVIMENT::INSTANCE* self, SHEET *sheet, sint x, sint y) { return self->y + y * sheet->cellHeight; }

}
#endif