#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "moblib/moblib.h"

using namespace std;

typedef short int sint;

#define index(x, y, width) x+y*width

class mlMapKey {
public:
    sint **keys = nullptr;
    sint size = 0;
    sint *localkeys = nullptr;
	sint localsize = 0;
    
    ~mlMapKey(){
        free(localkeys);
        free(keys);
    }
};

void _addkey(mlMapKey *self,sint *keys) {
	self->keys = (sint**)realloc(self->keys, ++self->size * sizeof(sint*));
	self->keys[self->size-1] = keys;
   }

void _addkey(mlMapKey *self, sint keys) {
	self->keys = (sint**)realloc(self->keys, ++self->size * sizeof(sint*));
	self->localkeys = (sint*)realloc(self->localkeys, ++self->localsize * sizeof(sint));
	self->localkeys[self->localsize - 1] = keys;
	self->keys[self->size - 1] = self->localkeys;
}

sint _key(mlMapKey *self, sint index) {
	if (index >= self->size) return -1;
	return *self->keys[index];
}

class mlMapLayer {
private:
	mlMapKey *layer = nullptr;
    sint _width = 0,
          _height = 0;

public:

	sint width() {
		return _width;
	}

	sint height() {
		return _height;
	}

	mlMapLayer(sint width,sint height) {

        this->_width = width;
        this->_height = height;
        layer = (mlMapKey*)calloc(sizeof(mlMapKey),width*height);
        
        for(int i=0;i<width*height;i++){
            layer[i] = mlMapKey();
        }
	}
    

    void addkey(sint x, sint y, sint val){
        if(x>=_width || y>=_height)return;
        _addkey(&layer[index(x,y,_width)], val);
    }
    
    void addkey(sint x, sint y, sint *val){
        if(x>=_width || y>=_height)return;
        _addkey(&layer[index(x,y,_width)], val);
    }

    sint key(sint x,sint y,sint i){
        if(x>=_width || y>=_height)return -1;
	    return _key(&layer[index(x,y,_width)], i);
        
    }

	sint keyLayer(sint x, sint y) {
		if (x >= _width || y >= _height)return -1;
		return layer[index(x, y, _width)].size;
	}

	mlMapLayer(){
		free(layer);
	}
};


class mlMapping : public mlMapLayer{
    
	mlSheet *sheet = nullptr;
	
	sint limx, limy, limw, limh;
	float *posX, *posY;

public:
    
    mlMapping(mlSheet *sheet,mlMovimentInstance *mov,sint width, sint height,
		sint limiter_x = 0, sint limiter_y = 0, sint limiter_w=-1,sint limiter_h=-1): mlMapLayer(width, height){
        this->sheet = sheet;
		posX = &mov->x;
		posY = &mov->y;
        limx = limiter_x;
        limy = limiter_y;
        limw = limiter_w;
        limh = limiter_h;
		
    }
    


    sint overdraw(sint x,sint y){

		return (*posX + x * sheet->width() + sheet->width() < limx ||
			    *posY + y * sheet->height() + sheet->height() < limx ||
				*posX + x * sheet->width()  > limx + limw ||
				*posY + y * sheet->height() > limy + limh);

    }
    
	sint keyX(sint x, sint y, sint i=0) {
		return sheet->posX(key(x, y, i));
	}

	sint keyY(sint x, sint y, sint i=0) {
		return sheet->posY(key(x, y, i));
	}

	sint X(sint x, sint y) {
		return *posX+x*sheet->width();
	}

	sint Y(sint x, sint y) {
		return *posY+y*sheet->height();
	}

	sint keyWidth() {
		return sheet->width();
	}

	sint keyHeight() {
		return sheet->height();
	}
};

#endif