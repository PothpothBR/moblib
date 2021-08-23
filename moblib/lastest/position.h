/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     / _|              |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/
#ifndef POSITION_H
#define POSITION_H

class MOB_POSITION {
public:
	float x = 0, y = 0;
	MOB_POSITION(){}
	MOB_POSITION(float x, float y) { this->x = x, this->y = y; }
};

class MOB_DIMENSION {
public:
	float width = 0, height = 0;
	MOB_DIMENSION(){}
	MOB_DIMENSION(float width, float height) { this->width = width, this->height = height; }
};

class MOB_FORM {
public:
	MOB_POSITION* position = nullptr;
	MOB_DIMENSION* dimension = nullptr;

	MOB_FORM() {}
	MOB_FORM(MOB_POSITION* position, MOB_DIMENSION* dimension) { this->position = position, this->dimension = dimension; }
};

#endif //POSITION_H