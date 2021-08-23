#ifndef _THREAD_H
#define _THREAD_H

#include "timing.h"
#include "debug_log.h"
	
// instancia o thread em si
class THREAD {
public:
	THREAD() {}
	THREAD* next = nullptr;
	void* obj = nullptr;
	unsigned short int id = 0;
};

// instancia uma fila para coleta inicial de treads
class CHANNELS {
public:
	TICKS** tick = nullptr;
	THREAD** head = nullptr;
	int channels = 0;
	int *channelID = nullptr;
	int *size = 0;
		
	~CHANNELS() {
			
		THREAD* tmp = nullptr;
		THREAD* tmpflip = nullptr;
		for (int i = 0;i < channels;i++) { // deleta todos o threads dos canais;
			tmp = head[i];
			for (int e = 0; e < size[i]; e++) {
				tmpflip = tmp->next;
				delete tmp->obj;
				delete tmp;
				tmp = tmpflip;
				delete tick[i];
			}
		}

		// o vetor de canais e deletado automaticamente

		delete tick; // deleta o timer
		free(channelID); // deleta os ID's
		free(size); // deleta o tamanho dos canais
	}

	void wait() { for (int i = 0;i < channels; i++) { tick[i]->wait(); } } // da o tempo de espera nessesario para disparar outro evento
	int getChanelById(int id) { for (int i = 0;i < channels;i++) { if (id == channelID[i]) { return i; } } return -1; }

};

THREAD* iniTHREAD(void *obj, int id) { THREAD* self = new THREAD; self->obj = obj; self->id = id; return self; }
		
void addchanel(CHANNELS* self, int id, float delay = 0, float FPS = 0) {
	self->channels++;// aumenta o numero de canais
	self->size = (int*)realloc(self->size, sizeof(int)*self->channels);// cria uma nova variavel para armazenar o tamanho do novo canal
	self->size[self->channels - 1] = 0;
	self->channelID = (int*)realloc(self->channelID, sizeof(int)*self->channels);// cria uma nova variavel para armazenar o ID do novo canal
	self->channelID[self->channels - 1] = id;
	self->head = (THREAD**)realloc(self->head, sizeof(THREAD*)*self->channels);// cria uma nova posicao no vetor, para uma lista encadeada de threads
	self->tick = (TICKS**)realloc(self->tick, sizeof(TICKS*)*self->channels);// cria uma nova variavel para armazenar o temporisador do novo canal
	self->tick[self->channels - 1] = new TICKS(delay, FPS);
}

void remchanel(CHANNELS* self, int id) {
	int index = self->getChanelById(id);
	self->channels--;// diminui o numero de canais;
	THREAD** tmpcopy = (THREAD**)calloc(self->channels, sizeof(THREAD*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;
	int* idcopy = (int*)calloc(self->channels, sizeof(int*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;
	int* sizecopy = (int*)calloc(self->channels, sizeof(int*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;
	TICKS** tickcopy = (TICKS**)calloc(self->channels, sizeof(TICKS*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;

	// apaga os threads do canal
	THREAD* tmp = nullptr;
	THREAD* tmpflip = nullptr;
	tmp = self->head[index];
	for (int e = 0; e < self->size[index]; e++) {
		tmpflip = tmp->next;
		delete tmp->obj;
		delete tmp;
		tmp = tmpflip;
	}
	// ------------------------

	int i = 0;
	for (;i < index;i++) {// copia ate a posicao de corte
		tmpcopy[i] = self->head[i];
		idcopy[i] = self->channelID[i];
		sizecopy[i] = self->size[i];
		tickcopy[i] = self->tick[i];
	}
	for (;i < self->channels;i++) {// pula a posicao de corte e continua a copiar
		tmpcopy[i] = self->head[i + 1];
		idcopy[i] = self->channelID[i + 1];
		sizecopy[i] = self->size[i + 1];
		tickcopy[i] = self->tick[i + 1];
	}

	free(self->head);// desaloca o vetor antigo
	self->head = tmpcopy;// e copia o novo vetor

	free(self->channelID);// desaloca o vetor antigo
	self->channelID = idcopy;// e copia o novo vetor

	free(self->size);// desaloca o vetor antigo
	self->size = sizecopy;// e copia o novo vetor

	free(self->tick);// desaloca o vetor antigo
	self->tick = tickcopy;

}

void addthread(CHANNELS* selfc, THREAD *self) {// se tiver passado o tempo dispara o evento, senao deleta o evento, se o id nao for encontrado deleta o evento;
			
	int i = selfc->getChanelById(self->id);
	if (i != -1 && selfc->tick[i]->trigger()) {
		selfc->size[i]++;
		self->next = selfc->head[i];
		selfc->head[i] = self;
		return;
	}
	delete self->obj;
	delete self;
}

void remthread(CHANNELS* self, int chanelid, int index) {
	int indexid = self->getChanelById(chanelid);// pega o index do canal pelo id
	if (indexid == -1 || self->size[indexid] - 1 < index) return;// se nao achar o id ou o index for maior que o tamanho da fila, para.
	self->size[indexid]--;// diminui o tamanho da fila
	THREAD* tmp = self->head[indexid]; // pega o header correspondente ao id
	if (index == 0) { self->head[indexid] = tmp->next; delete tmp; }// se o index for o primeiro item, remove...
	else {// ....senao, anda até o item e remove ele
		THREAD* back = nullptr;
		for (int i = 0;i < index;i++) { back = tmp; tmp = tmp->next; }
		back->next = tmp->next;
		delete tmp->obj;
		delete tmp;
	}
}

void debug(CHANNELS* self) {
	THREAD* tmp;
	debugLog("thread|info");
	debugLog("channels:", self->channels);
	debugLog("");
	for (int i = 0;i < self->channels;i++) {
		debugLog("chanel:", self->channelID[i], "size:", self->size[i]);
		tmp = self->head[i];
		for (int e = 0;e < self->size[i];e++) {
			debugLog("thread:", (int)tmp, "obj:", (int)tmp->obj, "id:", tmp->id);

			tmp = tmp->next;
		}
		debugLog("");
	}

}
	

#endif
