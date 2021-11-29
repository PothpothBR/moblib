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
class mlSheet {
public:
	sint  totalCells,
		  handleX[9], handleY[9],
		  *cellX, *cellY;
	float cellWidth, cellHeight;
	
	mlSheet(sint width,sint height,sint cols,sint rows) {

		debugLog("created obj <mlSheet>");
		debugLog("cols:" , cols);
		debugLog("rows:", rows);
		debugLog("width:", width);
		debugLog("height:", height);
		debugLog("totalCells:", cols*rows);

		sint w = this->cellWidth = width / cols;
		sint h = this->cellHeight = height / rows;
		this->totalCells = cols * rows;


		debugLog("cell: width:", w,"height:", h);

		sint hw = w / 2;
		sint hh = h / 2;

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

		this->cellX = (sint *) malloc(sizeof(sint) * this->totalCells);
		this->cellY = (sint *) malloc(sizeof(sint) * this->totalCells);

		for (sint index = 0; index < this->totalCells; index++) {
			cellX[index] = index % cols * w;
			cellY[index] = int(index / cols) * h;
		}

	}

	~mlSheet() {



		debugLog("destructing obj <mlSheet>");
		free(this->cellX);
		free(this->cellY);
        cellX = nullptr;
        cellY = nullptr;
	}

};

#endif
