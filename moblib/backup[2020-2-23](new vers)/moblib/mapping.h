#ifndef MAPPING_H
#define MAPPING_H

#include "debug_log.h"
typedef unsigned short int usint;
typedef  short int sint;

/*if (initalizer) {
			for (int w = 0;w < width;w++) {

				for (int h = 0;h < height;h++) {
					for (int i = 0;i < sizeofkeys;i++) {
						buffer[w][h] = &initalizer[w][h];
					}
				}
			}
		}*/

struct mlMapping {
private:
	sint ***buffer = nullptr;
public:
	usint bufferWidth,
		bufferHeight;

	mlMapping(const usint width, const usint height) {

		this->buffer = (sint ***)calloc(width, sizeof(sint **));
		for (int i = 0;i < width;i++) {
			this->buffer[i] = (sint **)calloc(height, sizeof(sint *));
			for (int y = 0;y < height;y++) {
				buffer[i][y] = nullptr;
			}
		}

		bufferHeight = height;
		bufferWidth = width;

	}

	void setKey(usint x, usint y, sint key) {
		if (x < bufferWidth && y < bufferHeight) {
			
			buffer[x][y] = (sint *) malloc(sizeof(sint));
			*buffer[x][y] = key;
		}
	}

	void setAnimKey(usint x, usint y, mlAnimation *referkey) {
		if (x <= bufferWidth && y <= bufferHeight) {
			buffer[x][y] = (sint *)malloc(sizeof(sint));
			buffer[x][y] = &referkey->index;
		}
	}

	usint getKey(usint x, usint y){
		if (x < bufferWidth && y < bufferHeight && buffer[x][y]) {
				return *buffer[x][y];
		}
		return 0;
	}

	~mlMapping() {
		for (int w = 0;w < bufferWidth;w++) {

			for (int h = 0;h < bufferHeight;h++) {
					free(buffer[w][h]);
			}
			free(buffer[w]);
		}
		free(buffer);
	}
};
#endif
