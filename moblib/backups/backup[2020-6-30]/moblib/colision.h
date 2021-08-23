#ifndef COLISION_H
#define COLISION_H

#include <cstdlib>

namespace COLLISION {

	const int IN = 0;  // <object::obj_colid> objeto esta dentro de outro;
	const int OUT = 1; // <object::obj_colid> objeto esta fora de outro; se a velocidade do objeto for maior que o tamanho do colisor, o objeto "pulara" ele;

	class COLID {
	public:

		int width = 0, height = 0;
		float *x = 0, *y = 0;
		int *obj_pers_lado = nullptr;
		int ID;
		static int IDsize;
		int dir_mov = 0;

		COLID(float *position_x, float *position_y, int width, int height) {
			x = position_x, y = position_y;
			this->width = width, this->height = height;
			ID = IDsize++;
			obj_pers_lado = (int*)realloc(obj_pers_lado, sizeof(int*) * IDsize);
			obj_pers_lado[IDsize - 1] = 0;
		}

	};

	int COLID::IDsize = 0;

	

	bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
		return(x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
	}

	bool collision(COLID *self1, COLID *self2) {
		return(*self1->x < *self2->x + self2->width && *self1->x + self1->width > *self2->x && *self1->y < *self2->y + self2->height && *self1->y + self1->height > *self2->y);
	}

	bool collision(COLID *self1, int x2, int y2, int w2, int h2) {
		return(*self1->x < x2 + w2 && *self1->x + self1->width > x2 && *self1->y < y2 + h2 && *self1->y + self1->height > y2);
	}
}


#endif
