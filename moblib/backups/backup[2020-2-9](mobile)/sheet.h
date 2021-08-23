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


typedef unsigned short int usint;
typedef  short int sint;
// argumentos: <Width, Height, Cols, Rows>
struct SpriteSheet {
private:
	sint cols, rows,
		  totalCells,
		  cellWidth, cellHeight,
		  cellCenterX, cellCenterY,
		  handleX[9], handleY[9],
		  *cellsX, *cellsY;

	short int width, height;
public:
	sint getCellHeight() { return cellHeight; }
	sint getCellWidth() { return cellWidth; }
	sint getCellCenterX() { return cellCenterX; }
	sint getCellCenterY() { return cellCenterY; }
	sint getHandleX(usint index) { return handleX[index]; }
	sint getHandleY(usint index) { return handleY[index]; }
	sint getCellsX(usint index) { if (index < totalCells - 1) return cellsX[index]; return 0; }
	sint getCellsY(usint index) { if (index < totalCells - 1) return cellsY[index]; return 0; }
	sint getTotalCells() { return totalCells; }

	SpriteSheet(usint width,usint height,usint cols,usint rows) {

		debugLog("created obj <SpriteSheet>");

		this->cols = cols;
		this->rows = rows;
		this->width = width;
		this->height = height;

		debugLog("cols:" , cols);
		debugLog("rows:", rows);
		debugLog("width:", width);
		debugLog("height:", height);


		this->totalCells = cols * rows;
		debugLog("totalCells:", totalCells);

		usint h = this->cellWidth = width / cols;
		usint w = this->cellHeight = height / rows;

		debugLog("cell: width:", w,"height:", h);

		usint hw = this->cellCenterX = w / 2;
		usint hh = this->cellCenterY = h / 2;

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

		for (usint index = 0; index < this->totalCells; index++) {

			
			cellsX[index] = index % cols*w;
			cellsY[index] = int(index / cols) * h;

		}
		
	}
	
	~SpriteSheet() {



		debugLog("destructing obj <SpriteSheet>");
		this->cellsX = nullptr;
		free(this->cellsX);
		free(this->cellsY);
	}

};

#endif