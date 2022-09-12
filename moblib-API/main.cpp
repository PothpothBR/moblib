#include <iostream>

using namespace std;

#include "api-core.h"
#include "debug.h"


int main() {
	
	Core game(0.025);

	// definir objeto
	game.newObject("bird");
	game.newObject("player");
	game.newObject("tst");
	
	// criar animacao
	game.newAnimation("bird", "cima", 0, 3);
	game.newAnimation("bird", "baixo", 3, 3);
	game.newAnimation("bird", "direita", 6, 3);
	game.newAnimation("bird", "esquerda", 9, 3);

	game.newAnimation("tst", "baixo", 9, 8);

	game.newAnimation("player", "cima", 0, 3);
	game.newAnimation("player", "baixo", 3, 3);
	game.newAnimation("player", "direita", 6, 3);
	game.newAnimation("player", "esquerda", 9, 3);

	game.modAnimation("tst", "baixo", 0, 3);
	
	int fim = 18;

	while (fim) {
		
		game.flow();
		game.modAnimation("bird", "cima", none, none, none, fim);
		cout << game.animeIndex("bird", "cima");

		fim--;
	}	
	debug_core(&game);
	cin.get();
	
	return 0;
}
