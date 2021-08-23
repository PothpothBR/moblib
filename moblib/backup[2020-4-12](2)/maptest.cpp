
#include <iostream>
#include "moblib/moblib.h"

using namespace std;

typedef unsigned short int usint;
typedef short int sint;

class mlMapKey {
private:
    usint **keys = nullptr;
    usint size = 0;
    usint *localkeys = nullptr;
	usint localsize = 0;
public:

	usint rsize() {
		return size;
	}

	void addkey(usint *keys) {
		this->keys = (usint**)realloc(this->keys, ++size * sizeof(usint*));
		this->keys[size-1] = keys;
    }

	void addkey(usint keys) {
		this->keys = (usint**)realloc(this->keys, ++size * sizeof(usint*));
		localkeys = (usint*)realloc(localkeys, ++localsize * sizeof(usint));
		localkeys[localsize - 1] = keys;
		this->keys[size - 1] = localkeys;
	}

	usint key(usint index) {
		if (index >= size) return -1;
		return *keys[index];
	}

	void clear() {
		free(localkeys);
		free(keys);

		size = 0;
		localsize = 0;
	}
  
    mlMapKey(){
    }
    
    ~mlMapKey(){
        free(localkeys);
        free(keys);
    }
};


class mlMapLayer {
private:
	mlMapKey *layer = nullptr;
    usint width = 0,
    height = 0;

public:

	usint rwidth() {
		return width;
	}

	usint rheight() {
		return height;
	}

	mlMapLayer(usint width,usint height) {

        this->width = width;
        this->height = height;
        layer = (mlMapKey*)calloc(sizeof(mlMapKey),width*height);

	}

    usint addkey(usint x,usint y){

        if(x>=width || y>=height)return -1;
        return *layer[x+y*width];

    }
    

    void key(usint x,usint y,usint *adressval){
        if(x>=width || y>=height)return;
			layer[x + y * width] = adressval;
        }


	mlMapLayer(){
		free(layer);
	}
};


class mlMapMergedLayers {
private:
	usint ***layer = nullptr,
              size = 0,
              width = 0,
              height = 0;
public:
    mlMapMergedLayers(usint width,usint height) {

        this->width = width;
        this->height = height;
        size++;
        layer = (usint***)calloc(4,width*height);
        for(int i=0;i<width*height;i++){
            layer[i] =(usint**) malloc(4);
        }
            

	}

	usint rsize() {
		return size;
	}

	usint rwidth() {
		return width;
	}

	usint rheight() {
		return height;
	}

    void addlayer(){
        
    }

	~mlMapMergedLayers(){
	}
};

class mlMapping {
public:
    mlFormat* form = nullptr;



};


int main(){

   // mlMapLayer test(3,3);         //#9#
    usint testval = 0;
/*
	test.key(0, 0, &testval);  // 0
	test.key(0, 1, &testval); // 3
	test.key(0, 2, &testval); // 6
	test.key(1, 0, &testval); // 1
	test.key(1, 1, &testval); // 4
	test.key(1, 2, &testval); // 7
	test.key(2, 0, &testval); // 2
	test.key(2, 1, &testval); // 5
	test.key(2, 2, &testval); // 8
    for (usint i = 0; i < test.width; i++){
        for (usint e = 0; e < test.height; e++){
            cout << ' ' << test.key(i, e);
        }
        cout << endl;
    }*/

	mlMapKey test;

	test.addkey(&testval);
	test.addkey(4);
	cout << test.key(2);
	cin.get();
    return 0;
}
