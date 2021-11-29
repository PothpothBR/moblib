/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     /  _|             |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/
#ifndef SHEET_H
#define SHEET_H

// argumentos: <Width, Height, Cols, Rows>
class SHEET {
public:
	int  totalCells,
		  *cellX, *cellY;
	float handleX[9], handleY[9], cellWidth, cellHeight;
	
	SHEET(float width,float height,int cols,int rows) {

		float w = this->cellWidth = width / cols;
		float h = this->cellHeight = height / rows;
		this->totalCells = cols * rows;

		float hw = w / 2;
		float hh = h / 2;

		this->handleX[0] = 0;   this->handleY[0] = 0;
		this->handleX[1] = -hw; this->handleY[1] = 0;
		this->handleX[2] = -w;  this->handleY[2] = 0;
		this->handleX[3] = 0;   this->handleY[3] = -hh;
		this->handleX[4] = -hw; this->handleY[4] = -hh;
		this->handleX[5] = -w;  this->handleY[5] = -hh;
		this->handleX[6] = 0;   this->handleY[6] = -h;
		this->handleX[7] = -hw; this->handleY[7] = -h;
		this->handleX[8] = -w;  this->handleY[8] = -h;

		this->cellX = (int *) malloc(sizeof(int) * this->totalCells);
		this->cellY = (int *) malloc(sizeof(int) * this->totalCells);

		for (int index = 0; index < this->totalCells; index++) {
			cellX[index] = index % cols * w;
			cellY[index] = int(index / cols) * h;
		}

	}

	~SHEET() {
		free(this->cellX);
		free(this->cellY);
        cellX = nullptr;
        cellY = nullptr;
	}

};

#endif
