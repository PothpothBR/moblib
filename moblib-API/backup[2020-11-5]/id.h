#ifndef ID_H
#define ID_H

template <class ID, class LINK = ID>
class _Id {
public:

	ID** buffer_id = nullptr;
	LINK*** buffer_link = nullptr;

	/* buffer para os ids
		* e para os links
		*
		*o buffer e ponter-to-pointer-to-pointer por causa da mudanca de alocamento, evitando perder o endereco do id
	*/

	int	id_size = 0, // tamanho do buffer / quantidade de ids
	   *link_size = nullptr; // tamanho do buffer linkado ao id *a 1 posicao é do id*

	// cria um novo ID
	void newId(ID id) {

		buffer_id = (ID**)realloc(buffer_id, ++id_size * sizeof(ID*));// aumenta o tamanho do buffer de id
		buffer_id[id_size - 1] = nullptr; // inicia como nulo
		buffer_id[id_size - 1] = (ID*)realloc(buffer_id[id_size - 1], sizeof(ID));// cria uma posicao estavel para o id no buffer
		*buffer_id[id_size - 1] = ID(id); // adiciona o id a ultima posicao no buffer

		buffer_link = (LINK***)realloc(buffer_link, id_size * sizeof(LINK**));// aumenta o tamanho do buffer de link
		buffer_link[id_size - 1] = nullptr; // inicia como nulo

		link_size = (int*)realloc(link_size, id_size * sizeof(int));// aumenta o tamanho do buffer de posicoes de linkagem 
		link_size[id_size - 1] = 0; // inicia com 0

	}

	// cria um novo ID se nao houvere outro ja craido, retorna false se ja houver
	bool unicId(ID id) {

		for (int i = 0; i < id_size; i++) {
			if (*buffer_id[i] == id) return false;
		}

		buffer_id = (ID**)realloc(buffer_id, ++id_size * sizeof(ID*));// aumenta o tamanho do buffer de id
		buffer_id[id_size - 1] = nullptr; // inicia como nulo
		buffer_id[id_size - 1] = (ID*)realloc(buffer_id[id_size - 1], sizeof(ID));// cria uma posicao estavel para o id no buffer
		*buffer_id[id_size - 1] = ID(id); // adiciona o id a ultima posicao no buffer

		buffer_link = (LINK***)realloc(buffer_link, id_size * sizeof(LINK**));// aumenta o tamanho do buffer de link
		buffer_link[id_size - 1] = nullptr; // inicia como nulo

		link_size = (int*)realloc(link_size, id_size * sizeof(int));// aumenta o tamanho do buffer de posicoes de linkagem
		link_size[id_size - 1] = 0; // inicia com 0
		return true;
	}

	//linka um id ao primeiro id especifico, retorna false se nao houver
	bool linkId(LINK link, ID id) {

		for (int i = 0; i < id_size; i++) {

			if (id == *buffer_id[i]) { // se encontrar o id 

				buffer_link[i] = (LINK**)realloc(buffer_link[i], ++link_size[i] * sizeof(LINK*));// cria uma posicao para o linker no buffer
				buffer_link[i][link_size[i] - 1] = nullptr; // inicia como nulo

				buffer_link[i][link_size[i] - 1] = (LINK*)realloc(buffer_link[i][link_size[i] - 1], sizeof(LINK)); // cria o linker
				*buffer_link[i][link_size[i] - 1] = LINK(link); // alloca e atribui um valor

				return true;
			}

		}
		return false;
	}

	//retorna a primeira posicao do id especifico
	int id(ID id) {
		for (int i = 0; i < id_size; i++) {
			if (id == *buffer_id[i]) return i;
		}
		return -1;
	}

	// retorna a primeira posicao do id linkado ao link
	int linked(LINK id) {
		for (int i = 0; i < id_size; i++) {
			for (int e = 0; e < link_size[i]; e++) {
				if (id == *buffer_link[i][e])return i;
			}
		}
		return -1;
	}

	int linksInId(ID id) {
		for (int i = 0; i < id_size; i++) {
			if (id == *buffer_id[i]) return link_size[i];
		}
		return -1;
	}

	//retorna o primeiro id linkado ao link
	ID idLinked(LINK id) {
		for (int i = 0; i < id_size; i++) {
			for (int e = 0; e < link_size[i]; e++) {
				if (id == *buffer_link[i][e]) return *buffer_id[i];
			}
		}
		return (ID)nullptr;
	}

	// remove o link do id
	void unlinkId(LINK link, ID id) {

		for (int i = 0; i < id_size; i++) {
			if (id == *buffer_id[i]) {// encontra o id pai

					LINK** tmp = (LINK**)calloc(link_size[i] - 1, sizeof(LINK*));// cria um vetor temporario para alocar os links

					// remove o link do buffer
					for (int e = 0, tmp_e = 0; e < link_size[i]; e++, tmp_e++) {
						if (link == *buffer_link[i][e]) { free(buffer_link[i][e]); e++; }
							tmp[tmp_e] = buffer_link[i][e];

					}

					link_size[i]--;

					free(buffer_link[i]);// remove o buffer obsoleto
					buffer_link[i] = tmp; // copia o buffer cortado

					return;
			}
		}

	}

	//remove o id e todos os links asociados ao mesmo
	void unsetId(ID id) {

		ID** tmp = (ID**)calloc(id_size, sizeof(ID*));

		for (int i = 0, tmp_i = 0; i < id_size; i++, tmp_i++) {
			if (id == *buffer_id[i]) {free(buffer_id[i]); i++; }
			tmp[tmp_i] = buffer_id[i];
		}

		id_size--;

		free(buffer_id);
		buffer_id = tmp;

	}

	// retorna o endereco do link especifico
	LINK* ptrLink(LINK link, ID id) {

		for (int i = 0; i < id_size; i++) {
			if (id == *buffer_id[i]) {// se o id existir

				for (int e = 0; e < link_size[i]; e++) {
					if (link == *buffer_link[i][e]) {// e se o id de linkagem existir
						return buffer_link[i][e];
					}
				}
			}
		}
		return nullptr;
	}

	~_Id() {
		free(buffer_id);
		for (int i = 0; i < id_size; i++) {
			free(buffer_link[i]);
		}
		free(link_size);
		free(buffer_link);
	}

};

#endif // !ID_H
