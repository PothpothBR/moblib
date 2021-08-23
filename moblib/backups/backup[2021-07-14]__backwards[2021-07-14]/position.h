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

class MOB_SIZE {
public:
	float width = 0, height = 0;
	MOB_SIZE(){}
	MOB_SIZE(float width, float height) { this->width = width, this->height = height; }
};

class MOB_FORMAT {
public:
	MOB_POSITION* position = nullptr;
	MOB_SIZE* size = nullptr;

	MOB_FORMAT() {}
	MOB_FORMAT(MOB_POSITION* position, MOB_SIZE* size) { this->position = position, this->size = size; }
	~MOB_FORMAT() { delete position; delete size; }
};

#endif //POSITION_H