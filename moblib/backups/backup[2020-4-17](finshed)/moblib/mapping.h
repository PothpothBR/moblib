#ifndef MAP_H
#define MAP_H

#include "moblib/sheet.h"
#include "moblib/moviment.h"
#define index(x, y, width) x+y*width

typedef short int sint;

class mlMap {
private:
    sint _width = 0, _height = 0;
	sint ***_buffer = nullptr;
	sint *_layerSize = nullptr;
	sint **_locals = nullptr;
	sint _localSize = 0;
public:
	
	// <width, height>
	mlMap(sint w,sint h) {
        this->_width = w, this->_height = h;

		_buffer =(sint***) calloc(sizeof(sint**),w*h);

		_layerSize = (sint*)calloc(sizeof(sint), w*h);
        for(int i=0;i<w*h;i++){
			_layerSize =(sint*) calloc(sizeof(sint), w*h);
			_layerSize[i] = 0;
        }
	}

	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
    bool set(sint x, sint y, int val){
        if(x>=_width || y>=_height)return false;
		_buffer[index(x, y, _width)] = (sint**) realloc(_buffer[index(x, y, _width)], ++_layerSize[index(x, y, _width)] * sizeof(sint*));
		_locals = (sint**)realloc(_locals, sizeof(sint*)*++_localSize);
		_locals[_localSize - 1] =(sint*) malloc(sizeof(sint));
		*_locals[_localSize - 1] = val;
		_buffer[index(x, y, _width)][_layerSize[index(x, y, _width)] - 1] = _locals[_localSize - 1];
		return true;
    }
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool set(sint x, sint y, sint *val) {
		if (x >= _width || y >= _height)return false;
		_buffer[index(x, y, _width)] = (sint**)realloc(_buffer[index(x, y, _width)], ++_layerSize[index(x, y, _width)] * sizeof(sint*));
		_buffer[index(x, y, _width)][_layerSize[index(x, y, _width)] - 1] = val;
		return true;
	}
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool set(sint i, sint val) {
		if (i >= _width * _height)return false;
		_buffer[i] = (sint**)realloc(_buffer[i], ++_layerSize[i] * sizeof(sint*));
		_locals = (sint**)realloc(_locals, sizeof(sint*)*++_localSize);
		_locals[_localSize - 1] = (sint*)malloc(sizeof(sint));
		*_locals[_localSize - 1] = val;
		_buffer[i][_layerSize[i] - 1] = _locals[_localSize - 1];
		return true;
	}
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
	bool set(sint i, sint *val) {
		if (i >= _width * _height)return false;
		_buffer[i] = (sint**)realloc(_buffer[i], ++_layerSize[i] * sizeof(sint*));
		_buffer[i][_layerSize[i] - 1] = val;
		return true;
	}
   
	//retorna uma posicao no mapa, referente a sua camada 
    sint get(sint x,sint y,sint l){
		if (x >= _width || y >= _height && l >= _layerSize[index(x, y, _width)]) { debugLog("error at get get - x:", x,"y:",y); return -1; }
		return *_buffer[index(x, y, _width)][l];
    }
	//retorna uma posicao no mapa, referente a sua camada 
	sint get(sint i, sint l) {
		if (i >= _width * _height && l >= _layerSize[i]) { debugLog("error at get get - index:", i); return -1; }
		return *_buffer[i][l];
	}

	sint width() { return _width; } // retorna a largura do mapa
	sint height() { return _height; } // retorna a altura do mapa
	sint size() { return _width * _height; } //retorna o tamanho total do mapa
	
	sint sizel(sint x, sint y) { // retorna quantos camadas tem a posicao no mapa
		if (x >= _width || y >= _height) { debugLog("error at get buffer size - x:", x, "y:", y); return -1; }
		return _layerSize[index(x, y, _width)];
	}
	sint sizel(sint i) { // retorna quantos camadas tem a posicao no mapa
		if (i >= _width * _height) { debugLog("error at get buffer size - index", i); return -1; }
		return _layerSize[i];
	}

	~mlMap(){
		for (int i = 0;i < _localSize;i++) { free(_locals[i]); }
		free(_locals);

		for (int i = 0;i < _width * _height;i++) { free(_buffer[i]); }
		free(_buffer);
	}
	
};


class mlMapping {
	mlSheet *_sheet = nullptr;
	sint limx, limy, limw, limh;
	float *posX, *posY;
	bool _localMap = true;
public:
	mlMap *map = nullptr;
    // <mlSheet, mlMoviment, width, height, draw limiter:[x, y, width, height]>
    mlMapping(mlSheet *_sheet,mlMovimentInstance *mov,sint width, sint height, sint limiter_x = 0, sint limiter_y = 0, sint limiter_w=-1,sint limiter_h=-1){
		this->map = new mlMap(width, height);
        this->_sheet = _sheet;
		posX = &mov->x, posY = &mov->y;
        limx = limiter_x, limy = limiter_y, limw = limiter_w, limh = limiter_h;
    }
	//sobrescreve o mapa
	void overwriteMap(mlMap* map) { if (_localMap) { free(this->map); _localMap = false; } this->map = map; }
	//sobrescreve o mapa
	void overwriteMap(mlMap map) { if (_localMap) { free(this->map); } this->map = new mlMap(map); }

	// retorna true se esta fora do limite de desenho
    sint overdraw(sint x,sint y){ return (*posX + x * _sheet->width() + _sheet->width() < limx || *posY + y * _sheet->height() + _sheet->height() < limy || *posX + x * _sheet->width()  > limx + limw || *posY + y * _sheet->height() > limy + limh); }
    // retorna a posicao X  no spritesheet
	sint tileX(sint x, sint y, sint i=0) {return _sheet->posX(map->get(x, y, i));}
	// retorna a posicao Y  no spritesheet
	sint tileY(sint x, sint y, sint i=0) {return _sheet->posY(map->get(x, y, i));}
	// retorna a posicao X na tela
	sint X(sint x, sint y) {return *posX+x*_sheet->width();}
	// retorna a posicao Y na tela
	sint Y(sint x, sint y) {return *posY+y*_sheet->height();}
	// retorna a largura da posicao
	sint tileWidth() {return _sheet->width();}
	// retorna a altura da posicao
	sint tileHeight() {return _sheet->height();}

	// desaloca a memoria
	~mlMapping() {
		if (_localMap) free(map);

	}
};

#endif