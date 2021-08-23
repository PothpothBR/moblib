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

#ifndef MAP_H
#define MAP_H

#include "sheet.h"
#include "moviment.h"
#include "colision.h"
#include <iostream>
#include <fstream>

#define index(x, y, width) x+y*width

class MOB_MAP {
public:
	int width = 0, height = 0;
	int ***buffer = nullptr;
	int *mob_map_cell_size = nullptr;
	int **locals = nullptr;
	int localSize = 0;
		

	// <width, height>
	MOB_MAP(int w, int h) {
		this->width = w, this->height = h;

		buffer = (int***)calloc(sizeof(int**), w*h);
			

		mob_map_cell_size = (int*)calloc(sizeof(int), w*h);
			
		for (int i = 0;i < w*h;i++) mob_map_cell_size[i] = 0;
	}
	~MOB_MAP() {
		for (int i = 0;i < localSize && locals[i];i++) { free(locals[i]); }
		if(locals)free(locals);
		for (int i = 0;i < width * height && buffer[i];i++) { free(buffer[i]); }
		if(buffer)free(buffer);
	}
};

// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int x, int y, int val) {
	if (x >= self->width || y >= self->height)return false;
	self->buffer[index(x, y, self->width)] = (int**)realloc(self->buffer[index(x, y, self->width)], ++self->mob_map_cell_size[index(x, y, self->width)] * sizeof(int*));
	self->locals = (int**)realloc(self->locals, sizeof(int*)*++self->localSize);
	self->locals[self->localSize - 1] = (int*)malloc(sizeof(int));
	*self->locals[self->localSize - 1] = val;
	self->buffer[index(x, y, self->width)][self->mob_map_cell_size[index(x, y, self->width)] - 1] = self->locals[self->localSize - 1];
	return true;
}

// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int x, int y, int *val) {
	if (x >= self->width || y >= self->height)return false;
	self->buffer[index(x, y, self->width)] = (int**)realloc(self->buffer[index(x, y, self->width)], ++self->mob_map_cell_size[index(x, y, self->width)] * sizeof(int*));
	self->buffer[index(x, y, self->width)][self->mob_map_cell_size[index(x, y, self->width)] - 1] = val;
	return true;
}

// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int i, int val) {
	if (i >= self->width * self->height)return false;
	self->buffer[i] = (int**)realloc(self->buffer[i], ++self->mob_map_cell_size[i] * sizeof(int*));
	self->locals = (int**)realloc(self->locals, sizeof(int*)*++self->localSize);
	self->locals[self->localSize - 1] = (int*)malloc(sizeof(int));
	*self->locals[self->localSize - 1] = val;
	self->buffer[i][self->mob_map_cell_size[i] - 1] = self->locals[self->localSize - 1];
	return true;
}

// adiciona uma chave a uma posicao no mapa, se ja ouver chaves naquele mesmo local, sera adicionada a uma nova camada
bool mob_map_add(MOB_MAP *self, int i, int *val) {
	if (i >= self->width * self->height)return false;
	self->buffer[i] = (int**)realloc(self->buffer[i], ++self->mob_map_cell_size[i] * sizeof(int*));
	self->buffer[i][self->mob_map_cell_size[i] - 1] = val;
	return true;
}

// retorna o valor referente a uma celula no mapa, referente a camada <l>
int mob_map_cell(MOB_MAP *self, int x, int y, int l) {
	if (x >= self->width || y >= self->height || l >= self->mob_map_cell_size[index(x, y, self->width)]) { /* adicionar retorno de erro*/ return -1; }
	return *self->buffer[index(x, y, self->width)][l];
}

// retorna o valor referente a uma celula no mapa, referente a camada <l>
// não sei o pq mas esta desativado !?
int mob_map_cell(MOB_MAP *self, int i, int l) {
	//if (i >= self->width * self->height && l >= self->mob_map_cell_size[i]) { /* adicionar retorno de erro*/ return -1; }
	return *self->buffer[i][l];
}

// modifica uma posicao no mapa
void mob_map_modifier(MOB_MAP *self, int x, int y, int l, int val) {
	//if (x >= self->width || y >= self->height || l >= self->mob_map_cell_size[index(x, y, self->width)]) { /* adicionar retorno de erro*/ }
	*self->buffer[index(x, y, self->width)][l] = val;
}

// modifica uma posicao no mapa
void mob_map_modifier(MOB_MAP *self, int i, int l, int val) {
	//if (i >= self->width * self->height && l >= self->mob_map_cell_size[i]) { /* adicionar retorno de erro*/ }
	*self->buffer[i][l] = val;
}

// retorna quantas camadas tem a posicao no mapa
int mob_map_cell_size(MOB_MAP *self, int x, int y) { 
	if (x >= self->width || y >= self->height) { /* adicionar retorno de erro*/ return -1; }
	return self->mob_map_cell_size[index(x, y, self->width)];
}

// retorna quantos camadas tem a posicao no mapa
int mob_map_cell_size(MOB_MAP *self, int i) { 
	if (i >= self->width * self->height) { /* adicionar retorno de erro*/ return -1; }
	return self->mob_map_cell_size[i];
}

class MOB_MAPPING {
public:
	int limiter_x, limiter_y, limiter_w, limiter_h;
	bool local_map = true;
	MOB_MAP *map = nullptr;
	MOB_MAP *colid_map = nullptr;

	// <width, height, draw limiter:[x, y, width, height]>
	MOB_MAPPING(int width, int height, int limiter_x = 0, int limiter_y = 0, unsigned short int limiter_w = -1, unsigned short int limiter_h = -1) {
		this->map = new MOB_MAP(width, height);
		this->limiter_x = limiter_x, this->limiter_y = limiter_y, this->limiter_w = limiter_w, this->limiter_h = limiter_h;
	}

	MOB_MAPPING() {}

	// desaloca a memoria
	~MOB_MAPPING() { if (local_map) delete map; }
};




//sobrescreve o mapa
void mob_overwrite_map(MOB_MAPPING* self, MOB_MAP* map) { if (self->local_map) { delete self->map; self->local_map = false; } self->map = map; }

//sobrescreve o mapa
void mob_overwrite_map(MOB_MAPPING* self, MOB_MAP map) { if (self->local_map) { delete self->map; } self->local_map = true; self->map = new MOB_MAP(map); }

// retorna true se esta fora do limite de desenho
inline int mob_map_overdraw(MOB_MAPPING* map, MOB_MOVIMENT::INSTANCE* self, MOB_SHEET *sheet, int x, int y) {
	return (self->x + x * sheet->cellWidth + sheet->cellWidth  < map->limiter_x ||
		self->y + y * sheet->cellHeight + sheet->cellHeight < map->limiter_y ||
		self->x + x * sheet->cellWidth  > map->limiter_w ||
		self->y + y * sheet->cellHeight > map->limiter_h);
}

// retorna o a posicao X  no spritesheet
inline int mob_map_tile_x(MOB_MAPPING* self, MOB_SHEET * sheet, int x, int y, int i = 0) { return sheet->cellX[mob_map_cell(self->map, x, y, i)]; }

// retorna o a posicao Y  no spritesheet
inline int mob_map_tile_y(MOB_MAPPING* self, MOB_SHEET * sheet, int x, int y, int i = 0) { return sheet->cellY[mob_map_cell(self->map, x, y, i)]; }

// retorna a posicao X na tela
inline float mob_map_position_x(MOB_MOVIMENT::INSTANCE* self, MOB_SHEET * sheet, int x, int y) { return self->x + x * sheet->cellWidth; }

// retorna a posicao Y na tela
inline float mob_map_position_y(MOB_MOVIMENT::INSTANCE* self, MOB_SHEET * sheet, int x, int y) { return self->y + y * sheet->cellHeight; }

// carrega o mapa de uma data para um buffer temporario limpo.
void mob_load_map(MOB_MAPPING* self, std::string name) {

	std::ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {// pega a largura e altura do mapa
		if (var != '\n') {
			width++;
		}
		else {
			height++;
		}
	}

	width /= height + 1;

	file.close();
	file.open(name);

	int conv;
	MOB_MAP *tmp = new MOB_MAP(width, height);// cria um novo mapa
	int i = 0;
	while (file.get(var)) {// adiciona as chaves ao mapa

		if (var != '\n') {
			conv = var - 48;
			mob_map_add(tmp, i, conv);
			i++;
		}
	}

	mob_overwrite_map(self, tmp);// sobrescreve o mapa de origem
	self->local_map = true;
}

// carrega uma camada de uma data para um buffer temporario ja iniciado.
void mob_load_map_layer(MOB_MAPPING* self, std::string name) {

	std::ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {// pega a largura e altura do mapa
		if (var != '\n') {
			width++;
		}
		else {
			height++;
		}
	}

	width /= height + 1;

	file.close();
	file.open(name);

	int conv;
	int i = 0;
	while (file.get(var)) { // adiciona as chaves ao mapa

		if (var != '\n') {
			conv = var - 48;
			mob_map_add(self->map, i, conv);
			i++;
		}
	}


	self->local_map = true;
}

// nao testado
void mob_load_map_animation_layer(MOB_MAPPING* self, MOB_ANIM::ANIMATE* mob_anim, char key,  std::string name) {
	
	std::ifstream file;
	file.open(name);
	char var;

	int width = 0;
	int height = 0;

	while (file.get(var)) {// pega a largura e altura do mapa
		if (var != '\n') {
			width++;
		}
		else {
			height++;
		}
	}

	width /= height + 1;

	file.close();
	file.open(name);

	for (int i = 0; i < width * height; i++) { // adiciona as chaves ao mapa
		file.get(var);
		if (var == key) {
			mob_map_add(self->map, i, &mob_anim->index);
		}
	}

	self->local_map = false;
}

// classe simples em corrente para pontos de colizao
class COLID_POINT {
public:
	COLID_POINT* next = nullptr;
	int x, y, w, h;
};

// adiciona ao topo da corrente
void mob_add_to_chain(COLID_POINT** header, COLID_POINT* self) {
	self->next = *header;
	*header = self;
}

// destroi a corrente
void mod_delete_chain(COLID_POINT** header) {
	COLID_POINT* ptr = nullptr;
	while (*header) {
		ptr = *header;
		*header = (*header)->next;
		delete ptr;
	}
}

// remove o topo da corrente
void mod_remove_chain_header(COLID_POINT** header) {
	COLID_POINT* ptr = *header;
	*header = (*header)->next;
	delete ptr;
}

// remove uma posição da corrente
void mod_delete_chain_point(COLID_POINT** header, COLID_POINT* point) {
	if (*header == point) {
		mod_remove_chain_header(header);
		return;
	}
	for (COLID_POINT* ptr = *header, *before = nullptr; ptr; before = ptr, ptr = ptr->next) {
		if (ptr == point) {
			before->next = ptr->next;
			delete ptr;
			return;
		}
	}
}

// gera pontos de colizao eficientes
COLID_POINT* mob_map_fit_colid(MOB_MAP* self, MOB_MOVIMENT::INSTANCE* keyboard_pos, MOB_SHEET* map_tiles) {
	int w = 1, h = 1;
	MOB_MAP* col_map = new MOB_MAP(*self);// cria um novo mapa para a colizão
	
	// vetor para alocar os colizores
	COLID_POINT* header = nullptr;

	while (true) {
		for (register int y = 0; y < col_map->height; y++) {
			for (register int x = 0; x < col_map->width; x++) {
				//if (mob_map_overdraw(col_map, keyboard_pos, map_tiles, x, y)) continue;
				switch (mob_map_cell(col_map, x, y, 0)) {
				case 0:
					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, white);
					al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, gray, 1);
					break;
				case 1:
					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, red);
					al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, gray, 1);
					break;
				case 2:
					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, green);
					al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, gray, 1);
					break;
				}
			}
		}

		for (register int y = 0; y < col_map->height; y++) {
			for (register int x = 0; x < col_map->width; x++) {
				al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
					mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, al_map_rgba(0, 0, 0, 40));
				al_flip_display();

				if (!mob_map_cell(col_map, x, y, 0)) continue;

				for (register int c = x+1; c < col_map->width; c++) {
					
					if (mob_map_cell(col_map, c, y, 0)) w++;
					else break;

					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, c, y), mob_map_position_y(keyboard_pos, map_tiles, c, y),
						mob_map_position_x(keyboard_pos, map_tiles, c, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, c, y) + map_tiles->cellHeight, lightskyblue);
					al_flip_display();
				}
				
				for (register int c = y+1; c < col_map->height; c++) {
					if (mob_map_cell(col_map, x, c, 0)) h++;
					else break;

					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, c), mob_map_position_y(keyboard_pos, map_tiles, x, c),
						mob_map_position_x(keyboard_pos, map_tiles, x, c) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, c) + map_tiles->cellHeight, lightskyblue);
				}
				

				al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
					mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, red);
				al_flip_display();
				//al_rest(0.5);
				mob_add_to_chain(&header, new COLID_POINT);
				header->x = x;
				header->y = y;
				header->w = w;
				header->h = h;

				std::cout << " |x: " << header->x << " |y: " << header->y << " |w: " << header->w << " |h: " << header->h << endl;
				w = 1, h = 1;
			}
		}

		bool father_rem = false;
		for (register COLID_POINT* ptr = header; ptr;) {
			std::cout << " |x: " << ptr->x << " |y: " << ptr->y << " |w: " << ptr->w << " |h: " << ptr->h << endl;
			al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, ptr->x, ptr->y), mob_map_position_y(keyboard_pos, map_tiles, ptr->x, ptr->y),
				mob_map_position_x(keyboard_pos, map_tiles, ptr->x + ptr->w - 1, ptr->y + ptr->h - 1) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, ptr->x + ptr->w - 1, ptr->y + ptr->h - 1) + map_tiles->cellHeight, black, 4);
			al_flip_display();

			father_rem = false;
			/*for (register COLID_POINT* ptrtmp = header; ptrtmp;) {
				if (ptrtmp == ptr) break;
				COLID_POINT* remptr = nullptr;
				if (colid_out(ptr->x, ptr->y, ptr->w, ptr->h, ptrtmp->x, ptrtmp->y, ptrtmp->w, ptrtmp->h)) {
					if ((ptr->w * ptr->h) > (ptrtmp->w * ptrtmp->h)) {

						remptr = ptrtmp;
						ptrtmp = ptrtmp->next;
						mod_delete_chain_point(&header, remptr);
					}
					else {
						remptr = ptr;
						ptr = ptr->next;
						mod_delete_chain_point(&header, remptr);

						father_rem = true;
						break;
					}
				}
				else {
					ptrtmp = ptrtmp->next;
				}
			}*/
			if(!father_rem) ptr = ptr->next;
		}
		std::cout << "----------------------------------\n";

		al_rest(2.5);

		for (register int y = 0; y < col_map->height; y++) {
			for (register int x = 0; x < col_map->width; x++) {
				//if (mob_map_overdraw(col_map, keyboard_pos, map_tiles, x, y)) continue;
				switch (mob_map_cell(col_map, x, y, 0)) {
				case 0:
					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, white);
					al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, gray, 1);
					break;
				case 1:
					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, red);
					al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, gray, 1);
					break;
				case 2:
					al_draw_filled_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, green);
					al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, x, y), mob_map_position_y(keyboard_pos, map_tiles, x, y),
						mob_map_position_x(keyboard_pos, map_tiles, x, y) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, x, y) + map_tiles->cellHeight, gray, 1);
					break;
				}
			}
		}

		for (register COLID_POINT* ptr = header; ptr; ptr = ptr->next) {
			std::cout << " |x: " << ptr->x << " |y: " << ptr->y << " |w: " << ptr->w << " |h: " << ptr->h << endl;
			al_draw_rectangle(mob_map_position_x(keyboard_pos, map_tiles, ptr->x, ptr->y), mob_map_position_y(keyboard_pos, map_tiles, ptr->x, ptr->y),
				mob_map_position_x(keyboard_pos, map_tiles, ptr->x + ptr->w-1, ptr->y + ptr->h-1) + map_tiles->cellWidth, mob_map_position_y(keyboard_pos, map_tiles, ptr->x + ptr->w-1, ptr->y + ptr->h-1) + map_tiles->cellHeight, black, 4);
			al_flip_display();
		}
		al_rest(10);
		std::cout << "----------------------------------\n";
		

	}
	return header;
}
#endif