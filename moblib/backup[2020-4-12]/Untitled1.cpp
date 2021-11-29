#include <iostream>
#include "..//source//repos//testfight//testfight//moblib//moblib.h"

using namespace std;

typedef unsigned short int usint;
typedef  short int sint;

class mlMapLayer {
public:
};

class mlMapMergedLayer {
public:
	usint ****layer = nullptr,
              layers = 0,
              width = 0,
              height = 0;

    usint key(usint x,usint y){

        if(x>=width || y>=height)return -1;

        return **layer[x][y];


    }

	mlMapMergedLayer(usint width,usint height) {

        this->width = width;
        this->height = height;
        layers++;
        layer = (usint****)calloc(4,width);

        for (int i=0;i<width;i++){
            layer[i] = (usint***)calloc(4,height);
            for (int e=0;e<height;e++){
                layer[i][e] = (usint**)malloc(4);
            }

        }
	}

    void addkey(usint x,usint y,usint *adressval){
            *layer[x][y] = adressval;
        }


    void addlayer()


	~mlMapMergedLayer(){
	}
};

class mlMapping {
public:
    mlFormat* form = nullptr;



};


int main(){

    mlMapMergedLayer test(2,2);
    usint testval = 0;
    test.addkey(0,0,&testval);
    test.addkey(0,1,&testval);
    test.addkey(1,0,&testval);
    test.addkey(1,1,&testval);

    for (int i=0;i<test.width;i++){
        for (int e=0;e<test.height;e++){
            cout << ' ' << test.key(i,e);
        }
        cout << endl;
    }

    return 0;
}
