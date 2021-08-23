/*


						----------------------------------------------------
						|               Programa feito por                 |
						|     [Bruno Dalagnol] [2018] [versao: sei la]     |
						----------------------------------------------------
						|                                                  |
						|			  /\         /\       ___              |
						|			 /--\_______/--\     /  _|             |
						|			 |  Y       Y  |    / /                |
						|			 |    ==T==    |   / /                 |
						|			 \_____________/  / /                  |
						|				|  _____   \ / /                   |
						|				|           \ /                    |
						|				|  |--|  |\  |                     |
						|				|__||_|__||__|                     |
						----------------------------------------------------



	||||||    ||||||    ||||||			||||||    ||||||   |     |  ||     |    ||||||			||||||
	|    |   |      |   |     |			|     |   |     |  |     |  | |    |   |      |			|     |
	|    |  |        |  |     |			|     |   |     |  |     |  |  |   |  |        |		|      |
	|||||   |        |  | |||||			||||||    | |||||  |     |  |   |  |  |        |		|      |
	|       |        |  |  |			|     |   |  |     |     |  |    | |  |        |		|      |
	|        |      |   |   |			|     |   |   |    |	 |  |     ||   |      |			|     |
	|         ||||||    |    |			|||||||   |    |   |||||||  |      |    ||||||			||||||   |||

	*/
#ifndef SHEET_H
#define SHEET_H

#include "debug_log.h"


 
typedef  short int sint;
// argumentos: <Width, Height, Cols, Rows>
struct mlSheet {
private:
	sint cols, rows,
		  totalCells,
		  cellCenterX, cellCenterY,
		  handleX[9], handleY[9],
		  *cellsX, *cellsY;

	float cellWidth, cellHeight;

	short int _width, _height;
public:
	float height() { return cellHeight; }
	float width() { return cellWidth; }
	sint getCenterX() { return cellCenterX; }
	sint getCenterY() { return cellCenterY; }
	sint getHandleX(sint index) { return handleX[index]; }
	sint getHandleY(sint index) { return handleY[index]; }
	sint posX(sint index) { if (index < totalCells - 1 ) return cellsX[index]; return 0; }
	sint posY(sint index) { if (index < totalCells - 1) return cellsY[index]; return 0; }
	sint posX(sint *index) { if (*index < totalCells - 1) return cellsX[*index]; return 0; }
	sint posY(sint *index) { if (*index < totalCells - 1) return cellsY[*index]; return 0; }
	sint getCellsCount() { return totalCells; }

	mlSheet(sint width,sint height,sint cols,sint rows) {

		debugLog("created obj <mlSheet>");

		this->cols = cols;
		this->rows = rows;
		this->_width = width;
		this->_height = height;

		debugLog("cols:" , cols);
		debugLog("rows:", rows);
		debugLog("width:", width);
		debugLog("height:", height);


		this->totalCells = cols * rows;
		debugLog("totalCells:", totalCells);

		sint w = this->cellWidth = width / cols;
		sint h = this->cellHeight = height / rows;

		debugLog("cell: width:", w,"height:", h);

		sint hw = this->cellCenterX = w / 2;
		sint hh = this->cellCenterY = h / 2;

		debugLog("cellCenter: width:", hw, "height:", hh);

		this->handleX[0] = 0;   this->handleY[0] = 0;
		this->handleX[1] = -hw; this->handleY[1] = 0;
		this->handleX[2] = -w;  this->handleY[2] = 0;
		this->handleX[3] = 0;   this->handleY[3] = -hh;
		this->handleX[4] = -hw; this->handleY[4] = -hh;
		this->handleX[5] = -w;  this->handleY[5] = -hh;
		this->handleX[6] = 0;   this->handleY[6] = -h;
		this->handleX[7] = -hw; this->handleY[7] = -h;
		this->handleX[8] = -w;  this->handleY[8] = -h;

		this->cellsX = (sint *) malloc(sizeof(sint) * this->totalCells);
		this->cellsY = (sint *) malloc(sizeof(sint) * this->totalCells);

		for (sint index = 0; index < this->totalCells; index++) {


			cellsX[index] = index % cols * w;
			cellsY[index] = int(index / cols) * h;

		}

	}

	~mlSheet() {



		debugLog("destructing obj <mlSheet>");
		free(this->cellsX);
		free(this->cellsY);
        cellsX = nullptr;
        cellsY = nullptr;
	}

};

#endif
