#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "moblib/moblib.h"

using namespace std;

typedef short int sint;

#define index(x, y, width) x+y*width


class mlMapAnimInstance {

	sint _width = 0,
		 _height = 0,
		 keyInfoSize = 0,
		 keySize = 0,
	     **keyInfo = nullptr,
	     **key = nullptr;

public:

	mlMapAnimInstance() {

	}

	// retorna a altura do mapa
	sint width() {
		return _width;
	}
	// retorna a altura do mapa
	sint height() {
		return _height;
	}

	bool addkey(sint x, sint y, sint *val){

		key = (sint**)calloc(sizeof(sint*),++keySize);
		key[keySize - 1] = val;
		keyInfo = (sint**)calloc(sizeof(sint*), ++keyInfoSize);
		keyInfo[keyInfoSize - 1] = (sint*)calloc(sizeof(sint), 2);
		keyInfo[keyInfoSize - 1][0] = x;
		keyInfo[keyInfoSize - 1][1] = y;

		return;
	}

};

class mlMapInstance {
private:
	
    sint _width = 0,
         _height = 0;
	sint **layer = nullptr;
	sint *_layerSize = nullptr;
public:
	

	// retorna a altura do mapa
	sint width() {
		return _width;
	}
	// retorna a altura do mapa
	sint height() {
		return _height;
	}
	// <width, height>
	mlMapInstance(sint width,sint height) {

        this->_width = width;
        this->_height = height;

        layer = (sint**)calloc(sizeof(sint*),width*height);
		for (int i = 0;i < width*height;i++) {
			layer[i] = nullptr;
		}

		_layerSize = (sint*)calloc(sizeof(sint), width*height);

        for(int i=0;i<width*height;i++){
			_layerSize =(sint*) calloc(sizeof(sint), width*height);
			_layerSize[i] = 0;
        }
	}
    
	// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
    bool addkey(sint x, sint y, int val){
        if(x>=_width || y>=_height)return false;
	  //matriz      andar                              matriz    andar               matriz      andar<1 posicao do layer> que é o tamanho

		layer[index(x, y, _width)] = (sint*) realloc(layer[index(x, y, _width)], ++_layerSize[index(x, y, _width)] * sizeof(sint));
		layer[index(x, y, _width)][_layerSize[index(x, y, _width)] - 1] = val;
    }
   
	//retorna uma posicao no mapa, referente a sua camada 
    sint key(sint x,sint y,sint i){
        if(x>=_width || y>=_height && i < _layerSize[index(x, y, _width)])return -1;
		return layer[index(x, y, _width)][i];
    }
	//retorna uma posicao no mapa, referente a sua camada 
	sint key(sint index,sint i){
		if (index >= _width*_height && i <= _layerSize[index])return -1;
		return layer[index][i];
	}
	// retorna quantos camadas tem a posicao no mapa
	sint layerSize(sint x, sint y) {
		if (x >= _width || y >= _height)return -1;
		return _layerSize[index(x, y, _width)];
	}
	// retorna quantos camadas tem a posicao no mapa
	sint layerSize(sint index) {
		if (index >= _width * _height )return -1;
		return _layerSize[index];
	}

	mlMapInstance(){
		for (int i = 0;i < _width*_height;i++) {
			free(layer[i]);
		}
		free(layer);
		free(_layerSize);
	}
};

class mlMap : public mlMapInstance{
    
	mlSheet *sheet = nullptr;
	sint limx, limy, limw, limh;
	float *posX, *posY;

public:
    // <mlSheet, mlMoviment, width, height, draw limiter:[x, y, width, height]>
    mlMap(mlSheet *sheet,mlMovimentInstance *mov,sint width, sint height,
		sint limiter_x = 0, sint limiter_y = 0, sint limiter_w=-1,sint limiter_h=-1): mlMapInstance(width, height){
        this->sheet = sheet;
		posX = &mov->x;
		posY = &mov->y;
        limx = limiter_x;
        limy = limiter_y;
        limw = limiter_w;
        limh = limiter_h;
		
    }
    

	// retorna se o tile esta fora do limite de desenho
    sint overdraw(sint x,sint y){

		return (*posX + x * sheet->width() + sheet->width() < limx ||
			    *posY + y * sheet->height() + sheet->height() < limx ||
				*posX + x * sheet->width()  > limx + limw ||
				*posY + y * sheet->height() > limy + limh);

    }
    // retorna a posicao X do tile no spritesheet
	sint keyX(sint x, sint y, sint i=0) {
		return sheet->posX(key(x, y, i));
	}
	// retorna a posicao Y do tile no spritesheet
	sint keyY(sint x, sint y, sint i=0) {
		return sheet->posY(key(x, y, i));
	}
	// retorna a posicao X do tile na tela
	sint X(sint x, sint y) {
		return *posX+x*sheet->width();
	}
	// retorna a posicao Y do tile na tela
	sint Y(sint x, sint y) {
		return *posY+y*sheet->height();
	}
	// retorna a largura do tile
	sint keyWidth() {
		return sheet->width();
	}
	// retorna a altura do tile
	sint keyHeight() {
		return sheet->height();
	}
};

#endif