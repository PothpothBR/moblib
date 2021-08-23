#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "id.h"
#include "C:/Users/dalag/google drive/backups/lomeo(old moblib)/lastest/moblib.h"
class _Animation {
public:
	float fps = 0.25; // default as 40fps
	int anim_instance_size = 0, // tamanho do buffer de instancias
		anim_size = 0; // tamanho do buffer de animacoes

	// para saber a posicao das instancias no buffer, e a hierarquia entre animations e instances
	_Id<int, const char**>* intern_ids = nullptr;

	//para saber a posicao das animations no buffer
	_Id<const char**>* anim_ids = nullptr;

	ANIM::INSTANCE** _instance = nullptr;
	ANIM::ANIMATE** _animate = nullptr;

	_Animation() {
		intern_ids = (_Id<int, const char**>*) malloc(sizeof(_Id<int, const char*>));
		*intern_ids = _Id<int, const char**>();

		anim_ids = (_Id<const char**>*) malloc(sizeof(_Id<const char*>));
		*anim_ids = _Id<const char**>();
	}

	~_Animation() {
		for (int i = 0; i < anim_instance_size; i++) {delete _instance[i];}
		free(_instance);
		for (int i = 0; i < anim_size; i++) { delete _animate[i]; }
		free(_animate);
		free(intern_ids);
		free(anim_ids);
	}

	// define o fps do sistema grafico 
	void setFPS(float fps) {

		this->fps = fps;

		for (int i = 0; i < anim_instance_size; i++) {
			_instance[i]->FPS = fps;
			_animate[i]->time->stettime(_instance[i]->delay,fps);

		}

	}

	// cria uma nova animacao, retorna false se ja houver uma instancia
	bool newAnimation(const char** id, int start, int range, int direction = ANIM::FLIP, float delay = 0, float jump = 0) {

		// procura por instancias iguais ja criadas...
		for (int i = 0; i < anim_instance_size; i++) {

			// ...se houver...
			if (_instance[i]->delay == delay &&
				_instance[i]->direction == direction &&
				_instance[i]->rangeOfCells == range - 1 &&
				_instance[i]->step == jump + 1) {

				// ...linka o id a instacia...
				intern_ids->linkId(id, *intern_ids->buffer_id[i]);

				// ...cria uma nova animacao...
				
				_animate = (ANIM::ANIMATE**) realloc(_animate, ++anim_size * sizeof(ANIM::ANIMATE*));

				// ... atribui a instancia compartilhada...
				_animate[anim_size - 1] = new ANIM::ANIMATE(_instance[intern_ids->linked(id)], start);

				// ... e adiciona o id a lista de animations
				anim_ids->newId(id);

				return false;
			}
		}

		// ...se nao houver cria uma nova instancia no heap...
		_instance = (ANIM::INSTANCE**) realloc(_instance, ++anim_instance_size * sizeof(ANIM::INSTANCE*));
		_instance[anim_instance_size - 1] = new ANIM::INSTANCE(range, direction, delay, fps, jump);;

		// ...e um novo id para a instancia
		intern_ids->newId(anim_instance_size - 1);

		//cria uma nova animacao para o id especifico
		_animate = (ANIM::ANIMATE**) realloc(_animate, ++anim_size * sizeof(ANIM::ANIMATE*));
		_animate[anim_size - 1] = new ANIM::ANIMATE(_instance[anim_instance_size - 1], start);

		// ...linka o id a instacia...
		intern_ids->linkId(id, anim_instance_size - 1);

		// ... e adiciona o id a lista de animations
		anim_ids->unicId(id);
		return true;

	}

	//retorna a animacao especifica do id, se nao existir retorna um erro
	ANIM::ANIMATE* getAnimation(const char** id) {
		return _animate[anim_ids->id(id)];
	}

	//modifica a animacao
	void modAnimation(const char** id, int start, int range = -1, int direction = -1, float delay = -1, float jump = -1) {
		// coleta o id da instancia
		int tmp_id = intern_ids->linked(id);
		// coleta a instancia
		ANIM::INSTANCE* tmp = _instance[tmp_id];
		

		// se a propriedade for igual nao a modificacão se for outro valor sera criado outra instancia
		if (((direction < 0) ? false : (tmp->direction != direction)) ||
			((range < 0) ? false : (tmp->rangeOfCells+1 != range)) ||
			((delay < 0) ? false : (tmp->delay != delay)) ||
			((jump < 0) ? false : (tmp->step-1 != jump))) {

			// se for diferente...
			for (int i = 0; i < anim_instance_size; i++) {

				// ...procura por instancias iguais, se nao for modificar a propriedade, verifica pela instancia
				if ((delay < 0) ? (_instance[i]->delay == tmp->delay) : (_instance[i]->delay == delay) &&
					(direction < 0) ? (_instance[i]->direction == tmp->direction) : (_instance[i]->direction == direction) &&
					(range < 0) ? (_instance[i]->rangeOfCells == tmp->rangeOfCells) : (_instance[i]->rangeOfCells == range - 1) &&
					(jump < 0) ? (_instance[i]->step == tmp->step) : (_instance[i]->step == jump + 1)) {

					// remove o id da instancia linkada
					intern_ids->unlinkId(id, intern_ids->idLinked(id));

					// ...linka o id a nova instacia...
					intern_ids->linkId(id, *intern_ids->buffer_id[i]);

					// e adiciona a instancia na animacao
					modAnimInstance(_animate[anim_ids->id(id)], _instance[i]);

					// e verifica se a instancia ficou vazia, se sim remove-a
					if (!intern_ids->linksInId(tmp_id))remInstance(tmp);

					return;
				}
			}

			// cria uma nova instancia para o id
			_instance = (ANIM::INSTANCE**) realloc(_instance, ++anim_instance_size * sizeof(ANIM::INSTANCE*));

			// aloca a instancia
			_instance[anim_instance_size - 1] = new ANIM::INSTANCE(*tmp);

			// remove o link da instancias
			intern_ids->unlinkId(id, intern_ids->idLinked(id));

			// e verifica se a instancia ficou vazia, se sim remove-a
			if (!intern_ids->linksInId(tmp_id))remInstance(tmp);

			// constroi a instancia
			constructInstance(_instance[anim_instance_size - 1], range, direction, delay, fps, jump);

			// e adiciona a instancia na animacao
			modAnimInstance(_animate[anim_ids->id(id)], _instance[anim_instance_size - 1]);

			// ...e um novo id para a instancia
			intern_ids->newId(anim_instance_size - 1);

			// ...linka o id a instacia...
			intern_ids->linkId(id, anim_instance_size - 1);
		}

		// se start for diferente modifica
		if (((start < 0) ? false :_animate[anim_ids->id(id)]->start != start)) {
			modAnimStart(_animate[anim_ids->id(id)], _instance[intern_ids->idLinked(id)]->direction, start);
		}
	}

	private:

		static void constructAnim(ANIM::ANIMATE* self, ANIM::INSTANCE* stance, int startCell = 0) { // nao e usado!
			if (self->time) delete self->time;
			self->stance = stance;
			(stance->direction == 2) ? self->index = startCell + 1 : self->index = startCell - 1;
			self->start = startCell;
			self->end = startCell + stance->rangeOfCells;
			self->flip = -(stance->step);
			self->time = new TICKS(stance->delay, stance->FPS);
		}

		static void constructInstance(ANIM::INSTANCE* self, sint rangeOfCells, sint direction = 0, float delay = 0, float FPS = 0, sint stepCell = 0) {
			if (direction >= 0)self->direction = direction;
			if (rangeOfCells >= 0)self->rangeOfCells = rangeOfCells - 1;
			if (delay >= 0)self->delay = delay;
			if (stepCell >= 0)self->step = stepCell + 1;
			if (FPS >= 0)self->FPS = FPS;
		}

		static void modAnimStart(ANIM::ANIMATE* self, int direction, int startCell = 0) {
			(direction == 2) ? self->index = startCell + 1 : self->index = startCell - 1;
			self->end += startCell - self->start;
			self->start = startCell;

		}

		static void modAnimInstance(ANIM::ANIMATE* self, ANIM::INSTANCE* stance) {
			if (self->time) delete self->time;
			self->stance = stance;
			self->end = self->start + stance->rangeOfCells;
			self->flip = -(stance->step);
			self->time = new TICKS(stance->delay, stance->FPS);
		}

		void remInstance(ANIM::INSTANCE* stance) {

			// aloca um buffer temporario
			ANIM::INSTANCE** tmp = (ANIM::INSTANCE**)calloc(anim_instance_size-1, sizeof(ANIM::INSTANCE*));

			// e cria um laco para percorrer o buffer
			for (int i = 0, tmp_i = 0; i < anim_instance_size; i++, tmp_i++) {
				// se encontrar o valor a ser removido libera-o e incrementa a posicao do buffer obsoleto
				if (stance == _instance[i]) { 
					free(_instance[i]);
					// remove o id da instancia
					intern_ids->unsetId(i);
					i++;
				}
				// faz a copia do buffer
				tmp[tmp_i] = _instance[i];

			}

			// decrementa a quantidade de instancias
			anim_instance_size--;
			// libera a memoria do buffer obsoleto
			free(_instance);
			// e copia o novo buffer cortado
			_instance = tmp;

		}

};

#endif // !ANIMATIONS_H

