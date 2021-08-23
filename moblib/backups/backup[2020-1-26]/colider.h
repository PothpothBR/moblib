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

	manual:


		como usar a funcao de movimento:

			deve-se definir estados para as funcoes:
				set_w() - set_s() - set_a() - set_d()
				obs. sendo cada uma equivalente a um estado de tecla <[presionada] | [nao presionada]>
			e depois realizar a chamada para a funcao:
				obj_mov(usint)

		como usar as funcoes de colisao:

			deve-se chamar a funcao de colisao com o objeto que deve-se colidir com outro:
				ex: object obj(5, 5, 10, 10); obj.obj_colid(<&otr_obj>, <flags>);
				colocando como ponteiro do tipo object* o outro objeto a se testar a colisao
				e colocando uma flag referente a forma de colisao


		flags:
			<object::obj_colid>:
				COLID_IN = 0;
					objeto esta dentro de outro;
				COLID_OUT = 1;
					objeto esta fora de outro; se a velocidade do objeto for maior que o tamanho do colisor, o objeto "pulara" ele;
				COLID_UP_FINE = 2;
					NUNCA atravessa para baixo
				COLID_DOWN_FINE = 3;
					NUNCA atravessa para cima
				COLID_LEFT_FINE = 4;
					NUNCA atravessa para direta
				COLID_RIGHT_FINE = 5;
					NUNCA atravessa para esquerda


		funcoes:

			object::object(sint position_x, sint position_y, usint width, usint height)
				construtor padrao:
					posicao inicial no eixo x;
					posicao inicial no eixo y;
					largura do objeto;
					altura do objeto;

			int object::obj_mov(sint velocity)
				funcao de movimento do personagem:
					velocidade do personagem;

			bool object::obj_colid(object* otr_obj, usint obj_in_out)
				colisor para o objeto chamador que atua no mesmo:
					o outro objeto que se deseja a colisao;
					flags;
						retona true caso aja uma colisao e false caso contrario

			bool object::obj_colid_invert(object* otr_obj, usint obj_in_out)
				colisor que atua no objeto de insercao por ponteiro nao no objeto chamador
				o outro objeto que se deseja a colisao;
				flags;
					retona true caso aja uma colisao e false caso contrario

			sint object::get_x(void) { return obj_pos_x; }
					retorna a posicao x;
				
			sint object::get_y(void) { return obj_pos_y; }
					retorna a posicao y;

			sint object::get_w(void) { return obj_w; }
					retorna a largura;

			sint object::get_h(void) { return obj_h; }
					retorna a altura;

			void object::set_w(bool state) { obj_click_w = state; }
				define um estado de <true == ativo> ou <false == inativo> para o w:
					valor true ou false;

			void object::set_s(bool state) { obj_click_s = state; }
				define um estado de <true == ativo> ou <false == inativo> para o s:
					valor true ou false;

			void object::set_a(bool state) { obj_click_a = state; }
				define um estado de <true == ativo> ou <false == inativo> para o a:
					valor true ou false;

			void object::set_d(bool state) { obj_click_d = state; }
				define um estado de <true == ativo> ou <false == inativo> para o d:
					valor true ou false;

			usint object::get_number() { return obj_number; }
					retorna o numero do objeto, o numero do objeto e definido na ordem de criacao dos objetos;

			bool obj_follow(object* otr, sint velocity, usint distance);
				faz um objeto te seguir, respeitando uma distancia limite se nessesario:
					o outr objeto;
					a velocidade;
					a distancia;
						retorna verdadeiro caso os objetos se encontrem, RESPEITANDO A DISTANCIA LIMITE;

			bool obj_follow_invert(object* otr, sint velocity, usint distance);
				faz o objeto seguir outro, respeitando uma distancia limite se nessesario:
					o outr objeto;
					a velocidade;
					a distancia;
						retorna verdadeiro caso os objetos se encontrem, RESPEITANDO A DISTANCIA LIMITE;
*/

// sistema de buffer principal adicionado
// interface basica no terminal adicionada
// sistema de coleta de dados adicionado
// sistema de leitura de dados adicionado
// sintaxe basica visual em allegro adicionada

// adicionar sistema que identifica cada obj_data
// adicionar sistema para coleta de posicoes para cada obj_data
// adicionar sistema para identificar qual funcao esta sendo usada
// adicionar sistema para identificar os sensores de colisao
// adicionar sistema para identificar colisao
// adicionar sistema para mostrar visualmente os objetos
// adicionar sistema para conversa por buffer externo entre: [projeto <--> object_v2.h --> object_v2.cpp]

#ifndef objetos_h
#define objetos_h

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>

typedef short int sint;
typedef unsigned short int usint;
typedef const unsigned short int c_usint;

using namespace std;


const usint IN = 0;  // <object::obj_colid> objeto esta dentro de outro;
const usint OUT = 1; // <object::obj_colid> objeto esta fora de outro; se a velocidade do objeto for maior que o tamanho do colisor, o objeto "pulara" ele;
const usint UP_FINE = 2; // NUNCA atravessa para baixo
const usint DOWN_FINE = 3; // NUNCA atravessa para cima
const usint LEFT_FINE = 4; // NUNCA atravessa para direta
const usint RIGHT_FINE = 5; // NUNCA atravessa para esquerda


class SpriteColision {
private:

	usint obj_w = 0, obj_h = 0;

	usint obj_vel = 0;
	bool obj_click_w = false;
	bool obj_click_a = false;
	bool obj_click_s = false;
	bool obj_click_d = false;

	usint obj_pers_lado[100] = { 0 };

	usint obj_number;
	static usint count_obj;
	usint dir_mov = 0;

public:

	sint obj_pos_x = 0; // nessesario em public pelo fato do uso nos colisores
	sint obj_pos_y = 0; // nessesario em public pelo fato do uso nos colisores

	SpriteColision(){}
	SpriteColision(sint position_x, sint position_y, usint width, usint height) {

		obj_pos_x = position_x;
		obj_pos_y = position_y;

		obj_w = width;
		obj_h = height;

		obj_number = count_obj++;

	} // construtor

	~SpriteColision() {
	}

	bool colid(SpriteColision*, usint); // colisor para o objeto chamador que atua no mesmo
	bool colid_invert(SpriteColision*, usint); // colisor que atua no objeto de insercao por ponteiro nao no objeto chamador

	bool verify_click(SpriteColision*);// novos
	bool verify_click(sint, sint, usint, usint);// novos

	bool follow(SpriteColision*, sint, usint);// novos
	bool follow_invert(SpriteColision*, sint, usint);// novos

	bool auto_mov(sint[100], sint[100], usint,usint);// novos
	bool auto_mov(SpriteColision*[100], usint, usint);// novos

	bool auto_mov(sint, sint, usint);// novos
	bool auto_mov(SpriteColision*,usint);// novos

	bool auto_mov(sint, sint, usint, usint);// novos
	bool auto_mov(SpriteColision*, usint , usint);// novos

	int mov(sint); // funcao de movimento do personagem obj_mov(velocidade)

	inline sint get_x(void) { // retorna a posicao x

		return obj_pos_x;
		

	} 
	inline sint get_y(void) { // retorna a posicao y

		return obj_pos_y;

	} 
	sint get_w(void) { // retorna a largura

		return obj_w; 

	}
	sint get_h(void) { // retorna a altura

		return obj_h;

	} 

	void set_w(bool state) { // define um estado de <true == ativo> ou <false == inativo> para o w

		obj_click_w = state; 

	} 
	void set_s(bool state) { // define um estado de <true == ativo> ou <false == inativo> para o s

		obj_click_s = state; 

	} 
	void set_a(bool state) { // define um estado de <true == ativo> ou <false == inativo> para o a

		obj_click_a = state;

	} 
	void set_d(bool state) { // define um estado de <true == ativo> ou <false == inativo> para o d

		obj_click_d = state;

	} 

	usint get_number() { return obj_number; }

}obj_HM;

usint SpriteColision::count_obj = 0;

int SpriteColision::mov(sint velocity) {

		obj_vel = velocity;

		if (obj_click_w && obj_click_a) { 

			obj_pos_y -= (obj_vel / 2.0f);
			obj_pos_x -= (obj_vel / 2.0f);

		}
		else if (obj_click_w && obj_click_d) {

			obj_pos_y -= (obj_vel / 2.0f);
			obj_pos_x += (obj_vel / 2.0f);

		}
		else if (obj_click_s && obj_click_a) {

			obj_pos_x -= (obj_vel / 2.0f);
			obj_pos_y += (obj_vel / 2.0f); 

		}
		else if (obj_click_s && obj_click_d) {

			obj_pos_x += (obj_vel / 2.0f);
			obj_pos_y += (obj_vel / 2.0f);

		}

		else if (obj_click_w) { 

			obj_pos_y -= obj_vel;

		}
		else if (obj_click_s) {

			obj_pos_y += obj_vel;

		}
		else if (obj_click_a) {

			obj_pos_x -= obj_vel; 

		}
		else if (obj_click_d) {

			obj_pos_x += obj_vel;

		}

	return 0;

}

bool SpriteColision::follow(SpriteColision* otr, sint velocity, usint distance) {

	bool colid = true;

	if (otr->obj_pos_x + otr->obj_w <= obj_pos_x - distance) {

		otr->obj_pos_x += velocity; colid = false;

	}
	if (otr->obj_pos_y + otr->obj_h <= obj_pos_y - distance) { 

		otr->obj_pos_y += velocity; colid = false;

	}
	if (otr->obj_pos_x >= obj_pos_x + obj_w + distance) {

		otr->obj_pos_x -= velocity; colid = false; 

	}
	if (otr->obj_pos_y >= obj_pos_y + obj_h + distance) {

		otr->obj_pos_y -= velocity; colid = false; 

	}

	return colid;
}
bool SpriteColision::follow_invert(SpriteColision* otr, sint velocity, usint distance) {

	bool colid = true;

	if (obj_pos_x + obj_w <= otr->obj_pos_x - distance) {

		obj_pos_x += velocity;
		colid = false;

	}
	if (obj_pos_y + obj_h <= otr->obj_pos_y - distance) {

		obj_pos_y += velocity;
		colid = false; 

	}
	if (obj_pos_x >= otr->obj_pos_x + otr->obj_w + distance) { 
		
		obj_pos_x -= velocity; 
		colid = false; 

	}
	if (obj_pos_y >= otr->obj_pos_y + otr->obj_h + distance) { 

		obj_pos_y -= velocity; 
		colid = false; 

	}

	return colid;
}
bool SpriteColision::colid(SpriteColision* otr_obj, usint obj_in_out) {

	bool colid; 
	colid = false;

	usint i_pers_lado = 0; 
	i_pers_lado = otr_obj->get_number();

	if (obj_in_out == IN) {

		if (obj_pos_x <= otr_obj->obj_pos_x - 1) {

			obj_pos_x = otr_obj->obj_pos_x - 1;
			colid = true;

		}
		if (obj_pos_y <= otr_obj->obj_pos_y - 1) {

			obj_pos_y = otr_obj->obj_pos_y - 1;
			colid = true; 

		}
		if (obj_pos_x + obj_w >= otr_obj->obj_pos_x + otr_obj->obj_w + 1) {

			obj_pos_x = otr_obj->obj_pos_x + (otr_obj->obj_w - obj_w) + 1; 
			colid = true;

		}
		if (obj_pos_y + obj_h >= otr_obj->obj_pos_y + otr_obj->obj_h + 1) { 

			obj_pos_y = otr_obj->obj_pos_y + (otr_obj->obj_h - obj_h) + 1;
			colid = true; 

		}

	}
	else if (obj_in_out == OUT) {

		bool lado[4];
		lado[0] = false;
		lado[1] = false; 
		lado[2] = false;
		lado[3] = false;

		if (obj_pos_y + obj_h >= otr_obj->obj_pos_y) { 

			lado[0] = true;

		}
		if (obj_pos_x <= otr_obj->obj_pos_x + otr_obj->obj_w) { 

			lado[1] = true;

		}
		if (obj_pos_y <= otr_obj->obj_pos_y + otr_obj->obj_h) {

			lado[2] = true;

		}
		if (obj_pos_x + obj_w >= otr_obj->obj_pos_x) { 

			lado[3] = true;

		}
		if (!lado[0]) { 

			obj_pers_lado[i_pers_lado] = 1; 

		}
		if (!lado[1]) { 

			obj_pers_lado[i_pers_lado] = 2;

		}
		if (!lado[2]) {

			obj_pers_lado[i_pers_lado] = 3;

		}
		if (!lado[3]) {

			obj_pers_lado[i_pers_lado] = 4;

		}

		if ((obj_pers_lado[i_pers_lado] == 1) && (lado[0] == true)) { 

			obj_pos_y = otr_obj->obj_pos_y - obj_h;
			colid = true;

		}
		if ((obj_pers_lado[i_pers_lado] == 2) && (lado[1] == true)) { 

			obj_pos_x = otr_obj->obj_pos_x + otr_obj->obj_w;
			colid = true;

		}
		if ((obj_pers_lado[i_pers_lado] == 3) && (lado[2] == true)) { 

			obj_pos_y = otr_obj->obj_pos_y + otr_obj->obj_h;
			colid = true;

		}
		if ((obj_pers_lado[i_pers_lado] == 4) && (lado[3] == true)) { 

			obj_pos_x = otr_obj->obj_pos_x - obj_w; 
			colid = true;

		}

		lado[0] = false;
		lado[1] = false;
		lado[2] = false;
		lado[3] = false;

}
	else if (obj_in_out == UP_FINE || obj_in_out == DOWN_FINE || obj_in_out == RIGHT_FINE || obj_in_out == LEFT_FINE) {

		bool none[4];

		bool lado[4];
		lado[0] = false;
		lado[1] = false;
		lado[2] = false; 
		lado[3] = false;

		if (obj_in_out == DOWN_FINE) {

			none[0] = false;

		}
		if (obj_in_out == RIGHT_FINE) { 

			none[1] = false; 

		}
		if (obj_in_out == UP_FINE) {

			none[2] = false; 

		}
		if (obj_in_out == LEFT_FINE) {

			none[3] = false;

		}
		if (obj_pos_y + obj_h >= otr_obj->obj_pos_y) { lado[0] = true; }
		if (obj_pos_x <= otr_obj->obj_pos_x + otr_obj->obj_w) { lado[1] = true; }
		if (obj_pos_y <= otr_obj->obj_pos_y + otr_obj->obj_h) { lado[2] = true; }
		if (obj_pos_x + obj_w >= otr_obj->obj_pos_x) { lado[3] = true; }
		if (!lado[0] && none[0]) {

			obj_pers_lado[i_pers_lado] = 1; 

		}
		if (!lado[1] && none[1]) {

			obj_pers_lado[i_pers_lado] = 2;

		}
		if (!lado[2] && none[2]) {

			obj_pers_lado[i_pers_lado] = 3;

		}
		if (!lado[3] && none[3]) { 

			obj_pers_lado[i_pers_lado] = 4;

		}
		if ((obj_pers_lado[i_pers_lado] == 1) && (lado[0] == true)) {

			obj_pos_y = otr_obj->obj_pos_y - obj_h; 
			colid = true;

		}
		if ((obj_pers_lado[i_pers_lado] == 2) && (lado[1] == true)) {

			obj_pos_x = otr_obj->obj_pos_x + otr_obj->obj_w;
			colid = true;

		}
		if ((obj_pers_lado[i_pers_lado] == 3) && (lado[2] == true)) { 

			obj_pos_y = otr_obj->obj_pos_y + otr_obj->obj_h; 
			colid = true;

		}
		if ((obj_pers_lado[i_pers_lado] == 4) && (lado[3] == true)) {

			obj_pos_x = otr_obj->obj_pos_x - obj_w;
			colid = true;

		}

		lado[0] = false; 
		lado[1] = false;
		lado[2] = false;
		lado[3] = false;

	}

	return colid; 

}

bool SpriteColision::colid_invert(SpriteColision* otr_obj, usint obj_in_out) {

	bool colid;
	colid = false;

	usint i_pers_lado = 0;
	i_pers_lado = otr_obj->get_number();

	if (obj_in_out == IN) {

		if (obj_pos_x <= otr_obj->obj_pos_x) { otr_obj->obj_pos_x = obj_pos_x; colid = true; }
		if (obj_pos_y <= otr_obj->obj_pos_y) { otr_obj->obj_pos_y = obj_pos_y; colid = true; }
		if (obj_pos_x + obj_w >= otr_obj->obj_pos_x + otr_obj->obj_w) { 
			otr_obj->obj_pos_x = obj_pos_x - (otr_obj->obj_w - obj_w); colid = true; 
		}
		if (obj_pos_y + obj_h >= otr_obj->obj_pos_y + otr_obj->obj_h) { 
			otr_obj->obj_pos_y = obj_pos_y - (otr_obj->obj_h - obj_h); colid = true; } 
	}
	
	else if (obj_in_out == OUT) {

		bool lado[4] = { false,false,false,false }; lado[0] = false; lado[1] = false; lado[2] = false; lado[3] = false;
		if (obj_pos_y + obj_h >= otr_obj->obj_pos_y) { 

			lado[0] = true; 

		}
		if (obj_pos_x <= otr_obj->obj_pos_x + otr_obj->obj_w) {

			lado[1] = true; 

		}
		if (obj_pos_y <= otr_obj->obj_pos_y + otr_obj->obj_h) {

			lado[2] = true;

		}
		if (obj_pos_x + obj_w >= otr_obj->obj_pos_x) { 

			lado[3] = true; 

		}

		if (!lado[0]) {

			obj_pers_lado[i_pers_lado] = 1; 

		}
		if (!lado[1]) {

			obj_pers_lado[i_pers_lado] = 2; 

		}
		if (!lado[2]) { 

			obj_pers_lado[i_pers_lado] = 3;

		}
		if (!lado[3]) { 

			obj_pers_lado[i_pers_lado] = 4;

		}

		if ((obj_pers_lado[i_pers_lado] == 1) && (lado[0] == true)) { 

			otr_obj->obj_pos_y = obj_pos_y + obj_h; colid = true; 

		}
		if ((obj_pers_lado[i_pers_lado] == 2) && (lado[1] == true)) { 

			otr_obj->obj_pos_x = obj_pos_x - otr_obj->obj_w; colid = true; 

		}
		if ((obj_pers_lado[i_pers_lado] == 3) && (lado[2] == true)) { 

			otr_obj->obj_pos_y = obj_pos_y - otr_obj->obj_h; colid = true; 

		}
		if ((obj_pers_lado[i_pers_lado] == 4) && (lado[3] == true)) {

			otr_obj->obj_pos_x = obj_pos_x + obj_w; colid = true;

		}
		
		lado[0] = false;
		lado[1] = false; 
		lado[2] = false;
		lado[3] = false;
	}

	return colid;
}

bool SpriteColision::verify_click(SpriteColision *otr_obj) {
	bool colid = false;

	if (obj_pos_x <= otr_obj->obj_pos_x) { otr_obj->obj_pos_x = obj_pos_x; colid = true; }
	if (obj_pos_y <= otr_obj->obj_pos_y) { otr_obj->obj_pos_y = obj_pos_y; colid = true; }
	if (obj_pos_x + obj_w >= otr_obj->obj_pos_x + otr_obj->obj_w) { 
		otr_obj->obj_pos_x = obj_pos_x - (otr_obj->obj_w - obj_w); colid = true; 
	}
	if (obj_pos_y + obj_h >= otr_obj->obj_pos_y + otr_obj->obj_h) { 
		otr_obj->obj_pos_y = obj_pos_y - (otr_obj->obj_h - obj_h); colid = true; 
	}

	return colid;
}

bool SpriteColision::verify_click(sint posx,sint posy,usint w, usint h) {
	bool colid = false;

	if (obj_pos_x <= posx) { posx = obj_pos_x; colid = true; }
	if (obj_pos_y <= posy) { posy = obj_pos_y; colid = true; }
	if (obj_pos_x + obj_w >= posx + w) { posx = obj_pos_x - (w - obj_w); colid = true; }
	if (obj_pos_y + obj_h >= posy + h) { posy = obj_pos_y - (h - obj_h); colid = true; }

	return colid;

}

bool SpriteColision::auto_mov(sint posx[100], sint posy[100], usint velocity, usint quanty_movments) {
	bool colid = true;

	if (obj_pos_x + obj_w <= posx[dir_mov]) {//movimento automatico de um ponto ao outro 
		obj_pos_x += velocity;
		colid = false;
	}
	if (obj_pos_y + obj_h <= posy[dir_mov]) {
		obj_pos_y += velocity;
		colid = false;
	}
	if (obj_pos_x >= posx[dir_mov]) {
		obj_pos_x -= velocity;
		colid = false;
	}
	if (obj_pos_y >= posy[dir_mov]) {
		obj_pos_y -= velocity;
		colid = false;
	}
	
	if (colid){ dir_mov++; }
	if (dir_mov > quanty_movments-1) { dir_mov = 0; }
	return colid;
}

bool SpriteColision::auto_mov(SpriteColision *otr[100], usint velocity, usint quanty_movments) {
	bool colid = true;

	if (obj_pos_x + obj_w <= otr[dir_mov]->obj_pos_x) {
		obj_pos_x += velocity;
		colid = false;
	}
	if (obj_pos_y + obj_h <= otr[dir_mov]->obj_pos_y) {
		obj_pos_y += velocity;
		colid = false;
	}
	if (obj_pos_x >= otr[dir_mov]->obj_pos_x) {
		obj_pos_x -= velocity;
		colid = false;
	}
	if (obj_pos_y >= otr[dir_mov]->obj_pos_y) {
		obj_pos_y -= velocity;
		colid = false;
	}

	if (colid) { dir_mov++; }
	if (dir_mov > quanty_movments - 1) { dir_mov = 0; }
	return colid;
}

bool SpriteColision::auto_mov(sint posx,sint posy,usint velocity) {
	bool colid = true;

	if (obj_pos_x + obj_w < posx) {//movimento automatico de um ponto ao outro 
		obj_pos_x += velocity;
		colid = false;
	}
	if (obj_pos_y + obj_h < posy) {
		obj_pos_y += velocity;
		colid = false;
	}
	if (obj_pos_x > posx) {
		obj_pos_x -= velocity;
		colid = false;
	}
	if (obj_pos_y > posy) {
		obj_pos_y -= velocity;
		colid = false;
	}

	return colid;
}
bool SpriteColision::auto_mov(SpriteColision *otr,usint velocity) {//movimento automatico de um ponto ao outro 
	bool colid = true;

	if (obj_pos_x + obj_w <= otr->obj_pos_x) {
		obj_pos_x += velocity;
		colid = false;
	}
	if (obj_pos_y + obj_h <= otr->obj_pos_y) {
		obj_pos_y += velocity;
		colid = false;
	}
	if (obj_pos_x >= otr->obj_pos_x) {
		obj_pos_x -= velocity;
		colid = false;
	}
	if (obj_pos_y >= otr->obj_pos_y) {
		obj_pos_y -= velocity;
		colid = false;
	}

	return colid;
}

// deixar tudo referente a movimento com float invez de sint

bool SpriteColision::auto_mov(sint posx, sint posy, usint velocity, usint random) {//movimento automatico de um ponto ao outro com variacao na velocidade
	srand(time(NULL));
	random = rand() % random; // o que acresentar
	double rands = rand() % 9; // sinal + -
	if (rands < 5) { 
		rands = true; 
	}
	if (rands >= 5) { 
		rands = false;
	}

	bool colid = true;
	if (obj_pos_x + obj_w < posx) {
		if (rands)obj_pos_x += velocity + random;
		if (!rands)obj_pos_x += velocity - random;
		colid = false;
	}
	if (obj_pos_y + obj_h < posy) {
		if (rands)obj_pos_y += velocity + random;
		if (!rands)obj_pos_y += velocity - random;
		colid = false;
	}
	if (obj_pos_x > posx) {
		if (rands)obj_pos_x -= velocity + random;
		if (!rands)obj_pos_x -= velocity - random;
		colid = false;
	}
	if (obj_pos_y > posy) {
		if (rands)obj_pos_y -= velocity + random;
		if (!rands)obj_pos_y -= velocity - random;
		colid = false;
	}
	return colid;
}

bool SpriteColision::auto_mov(SpriteColision *otr, usint velocity, usint random) { //movimento automatico de um ponto ao outro com variacao na velocidade
	srand(time(NULL));
	random = rand() % random; // o que acresentar
	double rands = rand() % 9; // sinal + -
	if (rands < 5)rands = true;
	if (rands >= 5)rands = false;

	bool colid = true;
	if (obj_pos_x + obj_w <= otr->obj_pos_x) {
		if (rands)obj_pos_x += velocity + random / 2;
		if (!rands)obj_pos_x += velocity - random;
		colid = false;
	}
	if (obj_pos_y + obj_h <= otr->obj_pos_y) {
		if (rands)obj_pos_y += velocity + random / 2;
		if (!rands)obj_pos_y += velocity - random;
		colid = false;
	}
	if (obj_pos_x >= otr->obj_pos_x) {
		if (rands)obj_pos_x -= velocity + random;
		if (!rands)obj_pos_x -= velocity - random / 2;
		colid = false;
	}
	if (obj_pos_y >= otr->obj_pos_y) {
		if (rands)obj_pos_y -= velocity + random;
		if (!rands)obj_pos_y -= velocity - random / 2;
		colid = false;
	}

	return colid;
}

#endif