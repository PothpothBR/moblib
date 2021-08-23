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
#ifndef SPRITES1F_H
#define SPRITES1F_H

#include "debug_log.h"


typedef unsigned short int usint;

struct SpriteSheet {

	usint cols, rows,
		  totalCells,
		  cellWidth, cellHeight,
		  cellCenter[2],
		  handleX[9], handleY[9],
		  *cellsX, *cellsY;

	short int width, height;

	explicit  SpriteSheet(usint width,usint height,usint cols,usint rows) {

		debugLog("created obj <Sprite_firstFloor>");

		this->cols = cols;
		this->rows = rows;
		this->width = width;
		this->height = height;

		debugLog("cols: " , cols);
		debugLog("rows: ", rows);
		debugLog("width: ", width);
		debugLog("height: ", height);


		this->totalCells = cols * rows;
		debugLog("totalCells: ", totalCells);

		usint h = this->cellWidth = width / cols;
		usint w = this->cellHeight = height / rows;

		debugLog("cell: width:", w," height: ", h);

		usint hw = this->cellCenter[0] = w / 2;
		usint hh = this->cellCenter[1] = h / 2;

		debugLog("cellCenter: width:", hw, " height: ", hh);

		this->handleX[0] = 0;   this->handleY[0] = 0;
		this->handleX[1] = -hw; this->handleY[1] = 0;
		this->handleX[2] = -w;  this->handleY[2] = 0;
		this->handleX[3] = 0;   this->handleY[3] = -hh;
		this->handleX[4] = -hw; this->handleY[4] = -hh;
		this->handleX[5] = -w;  this->handleY[5] = -hh;
		this->handleX[6] = 0;   this->handleY[6] = -h;
		this->handleX[7] = -hw; this->handleY[7] = -h;
		this->handleX[8] = -w;  this->handleY[8] = -h;

		this->cellsX = new usint[this->totalCells];
		this->cellsY = new usint[this->totalCells];


		for (usint index = 0; index < this->totalCells; index++) {


			cellsX[index] = index % cols*w;
			cellsY[index] = int(index / cols) * h;

		}
		
		
	}
	
	~SpriteSheet() {

		debugLog("destructing obj <Sprite_firstFloor>");


		delete[] this->cellsX;
		delete[] this->cellsY;

		this->cellsX = nullptr;
		this->cellsY = nullptr;
	}

};

#endif