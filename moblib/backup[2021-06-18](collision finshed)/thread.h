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

#ifndef _THREAD_H
#define _THREAD_H

#include "timing.h"
#include <cstdlib>

// cria uma capsula que armazena uma classe, que ao ir para o canal, pode ser manipulado
class MOB_THREAD {
public:
	//construtor
	MOB_THREAD() { }

	// para lista encadeada
	MOB_THREAD* next = nullptr;
	
	// o objeto
	void* object = nullptr;

	//o ID do objeto
	unsigned short int ID = 0;
};

// cria uma fila para armazenar os threads, aonde pode-se iterar sobre essa fila coletando os threads para uso
// e removendo-os se nescessario
class MOB_THREAD_CHANNEL {
public:

	// contador
	MOB_TICKS** tick = nullptr;
	
	// inicio da lista encadeada de threads
	MOB_THREAD** head = nullptr;

	//numero de canais criados
	int channels = 0;

	// ID do canal especifico
	int *channel_ID = nullptr;
	
	// numero de threads no canal
	int *channel_size = nullptr;
		
	// construtor vazio
	MOB_THREAD_CHANNEL() {}

	// destrutor padrao
	~MOB_THREAD_CHANNEL() {
			
		MOB_THREAD* tmp = nullptr;
		MOB_THREAD* tmpflip = nullptr;

		// deleta todos o threads dos canais;
		for (int i = 0;i < channels;i++) {
			tmp = head[i];
			for (int e = 0; e < channel_size[i]; e++) {
				tmpflip = tmp->next;
				delete tmp->object;
				delete tmp;
				tmp = tmpflip;
				delete tick[i];
			}
		}

		 // deleta o timer
		delete tick;

		// deleta os ID's
		free(channel_ID);

		// deleta o tamanho dos canais
		free(channel_size);
		
	}

	// da o tempo de espera para disparar outro eventos em todos dos threads
	void wait() { for (int i = 0;i < channels; i++) { tick[i]->wait(); } }

	// retorna o canal especifico pelo seu ID
	int get_channel_by_ID(int ID) { for (int i = 0;i < channels;i++) { if (ID == channel_ID[i]) { return i; } } return -1; }
};

// inicia um thread de forma simplificada
MOB_THREAD* mob_init_thread(void *object, int ID) { MOB_THREAD* self = new MOB_THREAD; self->object = object; self->ID = ID; return self; }
		
// 
void mob_add_channel(MOB_THREAD_CHANNEL* self, int ID, float delay = 0, float FPS = 0) {
	self->channels++;// aumenta o numero de canais
	self->channel_size = (int*)realloc(self->channel_size, sizeof(int)*self->channels);// cria uma nova variavel para armazenar o tamanho do novo canal
	self->channel_size[self->channels - 1] = 0;
	self->channel_ID = (int*)realloc(self->channel_ID, sizeof(int)*self->channels);// cria uma nova variavel para armazenar o ID do novo canal
	self->channel_ID[self->channels - 1] = ID;
	self->head = (MOB_THREAD**)realloc(self->head, sizeof(MOB_THREAD*)*self->channels);// cria uma nova posicao no vetor, para uma lista encadeada de threads
	self->tick = (MOB_TICKS**)realloc(self->tick, sizeof(MOB_TICKS*)*self->channels);// cria uma nova variavel para armazenar o temporisador do novo canal
	self->tick[self->channels - 1] = new MOB_TICKS(delay, FPS);
}

void mob_remove_channel(MOB_THREAD_CHANNEL* self, int ID) {
	int index = self->get_channel_by_ID(ID);
	self->channels--;// diminui o numero de canais;
	MOB_THREAD** tmpcopy = (MOB_THREAD**)calloc(self->channels, sizeof(MOB_THREAD*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;
	int* idcopy = (int*)calloc(self->channels, sizeof(int*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;
	int* sizecopy = (int*)calloc(self->channels, sizeof(int*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;
	MOB_TICKS** tickcopy = (MOB_TICKS**)calloc(self->channels, sizeof(MOB_TICKS*));// cria um vetor para armazenar temporiariamente o novo vetor cortado;

	// apaga os threads do canal
	MOB_THREAD* tmp = nullptr;
	MOB_THREAD* tmpflip = nullptr;
	tmp = self->head[index];
	for (int e = 0; e < self->channel_size[index]; e++) {
		tmpflip = tmp->next;
		delete tmp->object;
		delete tmp;
		tmp = tmpflip;
	}
	// ------------------------

	int i = 0;
	for (;i < index;i++) {// copia ate a posicao de corte
		tmpcopy[i] = self->head[i];
		idcopy[i] = self->channel_ID[i];
		sizecopy[i] = self->channel_size[i];
		tickcopy[i] = self->tick[i];
	}
	for (;i < self->channels;i++) {// pula a posicao de corte e continua a copiar
		tmpcopy[i] = self->head[i + 1];
		idcopy[i] = self->channel_ID[i + 1];
		sizecopy[i] = self->channel_size[i + 1];
		tickcopy[i] = self->tick[i + 1];
	}

	free(self->head);// desaloca o vetor antigo
	self->head = tmpcopy;// e copia o novo vetor

	free(self->channel_ID);// desaloca o vetor antigo
	self->channel_ID = idcopy;// e copia o novo vetor

	free(self->channel_size);// desaloca o vetor antigo
	self->channel_size = sizecopy;// e copia o novo vetor

	free(self->tick);// desaloca o vetor antigo
	self->tick = tickcopy;

}

void mob_add_thread(MOB_THREAD_CHANNEL* self_channel, MOB_THREAD *self) {// se tiver passado o tempo dispara o evento, senao deleta o evento, se o ID nao for encontrado deleta o evento;
			
	int i = self_channel->get_channel_by_ID(self->ID);
	if (i != -1 && self_channel->tick[i]->trigger()) {
		self_channel->channel_size[i]++;
		self->next = self_channel->head[i];
		self_channel->head[i] = self;
		return;
	}
	delete self->object;
	delete self;
}

void mob_remove_thread(MOB_THREAD_CHANNEL* self, int channel_ID, int index) {
	int indexid = self->get_channel_by_ID(channel_ID);// pega o index do canal pelo ID
	if (indexid == -1 || self->channel_size[indexid] - 1 < index) return;// se nao achar o ID ou o index for maior que o tamanho da fila, para.
	self->channel_size[indexid]--;// diminui o tamanho da fila
	MOB_THREAD* tmp = self->head[indexid]; // pega o header correspondente ao ID
	if (index == 0) { self->head[indexid] = tmp->next; delete tmp; }// se o index for o primeiro item, remove...
	else {// ....senao, anda até o item e remove ele
		MOB_THREAD* back = nullptr;
		for (int i = 0;i < index;i++) { back = tmp; tmp = tmp->next; }
		back->next = tmp->next;
		delete tmp->object;
		delete tmp;
	}
}
/*
void debug(MOB_THREAD_CHANNEL* self) {
	MOB_THREAD* tmp;
	debugLog("thread|info");
	debugLog("channels:", self->channels);
	debugLog("");
	for (int i = 0;i < self->channels;i++) {
		debugLog("channel:", self->channel_ID[i], "channel_size:", self->channel_size[i]);
		tmp = self->head[i];
		for (int e = 0;e < self->channel_size[i];e++) {
			debugLog("thread:", (int)tmp, "object:", (int)tmp->object, "ID:", tmp->ID);

			tmp = tmp->next;
		}
		debugLog("");
	}

}*/

#endif
