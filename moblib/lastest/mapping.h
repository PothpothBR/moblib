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

#include "position.h"
#include "sheet.h"
#include "moviment.h"
#include "colision.h"
#include "animation.h"
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
	if (i >= self->width * self->height && l >= self->mob_map_cell_size[i]) { /* adicionar retorno de erro*/ return -1; }
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

MOB_MAP* mob_map_clone(MOB_MAP* self, int layer) {
	MOB_MAP* clone = new MOB_MAP(self->width, self->height);
	for (register int i = 0; i < self->width * self->height; i++) {
		mob_map_add(clone, i, mob_map_cell(self, i, layer));
	}
	return clone;
}

// classe simples em corrente para pontos de colizao
class MOB_FORM_CHAIN {
public:
	MOB_FORM_CHAIN* next = nullptr;
	MOB_FORM form;
	~MOB_FORM_CHAIN() {
		delete form.position;
		delete form.dimension;
	}
};

MOB_FORM_CHAIN* mob_create_form_chain(float x, float y, float width, int height) {
	MOB_FORM_CHAIN* self = new MOB_FORM_CHAIN;
	self->form.position = new MOB_POSITION(x, y);
	self->form.dimension = new MOB_DIMENSION(width, height);
	return self;
}

// adiciona ao topo da corrente
void mob_add_to_chain(MOB_FORM_CHAIN** header, MOB_FORM_CHAIN* self) {
	self->next = *header;
	*header = self;
}

// destroi a corrente
void mod_delete_chain(MOB_FORM_CHAIN** header) {
	MOB_FORM_CHAIN* ptr = nullptr;
	while (*header) {
		ptr = *header;
		*header = (*header)->next;
		delete ptr;
	}
}

// remove o topo da corrente
void mod_remove_chain_header(MOB_FORM_CHAIN** header) {
	MOB_FORM_CHAIN* ptr = *header;
	*header = (*header)->next;
	delete ptr;
}

// remove uma posição da corrente
void mod_delete_chain_point(MOB_FORM_CHAIN** header, MOB_FORM_CHAIN* point) {
	if (*header == point) {
		mod_remove_chain_header(header);
		return;
	}
	for (MOB_FORM_CHAIN* ptr = (*header)->next, *before = *header; ptr; before = ptr, ptr = ptr->next) {
		if (ptr == point) {
			before->next = ptr->next;
			delete ptr;
			return;
		}
	}
}

// gera pontos de colizao eficientes
MOB_FORM_CHAIN* mob_map_fit_rectangles(MOB_MAP* self) {
	//cria valores para iteracao 
	int w = 0, h = 0;
	// cria um novo mapa para a colizão
	MOB_MAP* col_map = mob_map_clone(self, 0);
	// vetor para alocar os colizores
	MOB_FORM_CHAIN* most_fit = mob_create_form_chain(0, 0, 0, 0);
	MOB_FORM_CHAIN* fit_header = nullptr;

	while (true) {
		for (register int y = 0; y < col_map->height; y++) {
			for (register int x = 0; x < col_map->width; x++) {

				// verifica se é uma posição valida, se nao for continue
				if (!mob_map_cell(col_map, x, y, 0)) continue;
				if (x > 0 && y > 0 && (mob_map_cell(col_map, x - 1, y, 0) || mob_map_cell(col_map, x, y - 1, 0))) continue;

				// pegue a largura <w> e altura <h>
				w = 0, h = 0;
				for (register int tmpx = x; tmpx < col_map->width; tmpx++, w++) if (!mob_map_cell(col_map, tmpx, y, 0)) break;
				for (register int tmpy = y; tmpy < col_map->height; tmpy++, h++) if (!mob_map_cell(col_map, x, tmpy, 0)) break;

				// se for um ponto isolado, adicione-o a cadeia final já que nao a como otimizar-lo e continue
				if (w == 1 && h == 1) {
					mob_add_to_chain(&fit_header, mob_create_form_chain(x, y, w, h));
					mob_map_modifier(col_map, x, y, 0, 0);
					continue;
				}

				// gere 2 retangulos um a partir da altura, referente ao eixo do x
				int tmph = 0;
				for (register int tmpy = y, tmpw = 0; tmpy < col_map->height; tmpy++, tmph++) {
					for (register int tmpx = x; tmpx < col_map->width; tmpx++, tmpw++) if (!mob_map_cell(col_map, tmpx, tmpy, 0)) break;
					if (tmpw < w || !mob_map_cell(col_map, x, tmpy, 0)) break;
					tmpw = 0;
				}

				// e outro a partir da largura, referente ao eixo do y
				int tmpw = 0;
				for (register int tmpx = x, tmph = 0; tmpx < col_map->width; tmpx++, tmpw++) {
					for (register int tmpy = y; tmpy < col_map->height; tmpy++, tmph++) if (!mob_map_cell(col_map, tmpx, tmpy, 0)) break;
					if (tmph < h || !mob_map_cell(col_map, tmpx, y, 0)) break;
					tmph = 0;
				}

				// verifica qual é o maior, e atruibui ao quadrado final
				(w * tmph > h * tmpw) ? h = tmph : w = tmpw;

				// verifica se o quadrado final é maior que o maior quadrado ja mapeado, se for, substitua-o
				if ((w * h) > (most_fit->form.dimension->width * most_fit->form.dimension->height))
					most_fit->form.position->x = x, most_fit->form.position->y = y, most_fit->form.dimension->width = w, most_fit->form.dimension->height = h;
			}
		}

		// se ainda houverem quadrados, insira o maior, senao retorne
		if (most_fit->form.dimension->width * most_fit->form.dimension->height)
			mob_add_to_chain(&fit_header, mob_create_form_chain(most_fit->form.position->x, most_fit->form.position->y, most_fit->form.dimension->width, most_fit->form.dimension->height));
		else break;
		// remova a area da colizao do mapa, pos ela ja esta o mais otimizada possivel
		for (register int y = most_fit->form.position->y; y < most_fit->form.position->y + most_fit->form.dimension->height; y++)
			for (register int x = most_fit->form.position->x; x < most_fit->form.position->x + most_fit->form.dimension->width; x++)
				mob_map_modifier(col_map, x, y, 0, 0);
		// limpe a classe de colizao antes de reutilizar
		most_fit->form.position->x = 0, most_fit->form.position->y = 0, most_fit->form.dimension->width = 0, most_fit->form.dimension->height = 0;
	}

	delete most_fit;
	return fit_header;
}

// o mapa nao desaloca a valiravel position, pois ele so usa ela a partir de outra classe
class MOB_MAPPING {
public:
	int limiter_x = 0, limiter_y = 0, limiter_w = 0, limiter_h = 0;
	bool local_map = true;
	MOB_MAP *map = nullptr;
	MOB_FORM_CHAIN *rectangle_list = nullptr;
	MOB_POSITION *position = nullptr;
	MOB_SHEET* sheet = nullptr;

	// <width, height, draw limiter:[x, y, width, height]>
	MOB_MAPPING(MOB_POSITION* position, MOB_SHEET* sheet, int limiter_x = 0, int limiter_y = 0, unsigned short int limiter_w = 0, unsigned short int limiter_h = 0) {
		this->position = position;
		this->sheet = sheet;
		this->map = new MOB_MAP(sheet->cell_count.width, sheet->cell_count.height);
		this->limiter_x = limiter_x, this->limiter_y = limiter_y, this->limiter_w = limiter_w, this->limiter_h = limiter_h;
	}

	MOB_MAPPING() {}

	// desaloca a memoria
	~MOB_MAPPING() { 
		if (local_map) { delete map; map = nullptr; }

		if (sheet) { delete sheet; sheet = nullptr;}
	}
};

//sobrescreve o mapa
void mob_overwrite_map(MOB_MAPPING* self, MOB_MAP* map) { if (self->local_map) { delete self->map; self->local_map = false; } self->map = map; }

//sobrescreve o mapa/// tudo errado
//void mob_overwrite_map(MOB_MAPPING* self, MOB_MAP map) { if (self->local_map) { delete self->map; } self->local_map = true; self->map = new MOB_MAP(map); }

// retorna true se esta fora do limite de desenho
inline int mob_map_overdraw(MOB_MAPPING* map, int x, int y) {
	return (map->position->x + x * map->sheet->cell_dimension.width + map->sheet->cell_dimension.width  < map->limiter_x ||
		    map->position->y + y * map->sheet->cell_dimension.height + map->sheet->cell_dimension.height < map->limiter_y ||
		    map->position->x + x * map->sheet->cell_dimension.width  > map->limiter_w ||
		    map->position->y + y * map->sheet->cell_dimension.height > map->limiter_h);
}

// retorna o a posicao X  no spritesheet
inline int mob_map_tile_x(MOB_MAPPING* self, int x, int y, int i = 0) { return self->sheet->cellX[mob_map_cell(self->map, x, y, i)]; }

// retorna o a posicao Y  no spritesheet
inline int mob_map_tile_y(MOB_MAPPING* self, int x, int y, int i = 0) { return self->sheet->cellY[mob_map_cell(self->map, x, y, i)]; }

// retorna a posicao X na tela
inline float mob_map_position_x(MOB_MAPPING* self, int x, int y) { return self->position->x + x * self->sheet->cell_dimension.width; }

// retorna a posicao Y na tela
inline float mob_map_position_y(MOB_MAPPING* self, int x, int y) { return self->position->y + y * self->sheet->cell_dimension.height; }

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

// gera retangulos eficientes para colizao usado como referencia >= 0 para posicçoes que colidem e < 0 para posicoes que nao colidem
void mob_generate_rectangle_map(MOB_MAPPING* self) {
	self->rectangle_list = mob_map_fit_rectangles(self->map);
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

// nao testado, insere um unico padrao de animação a partir de uma chave
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


#endif