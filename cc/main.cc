#include <iostream>
#include "Game.h"

int main() {
	// create a game with dispersal of 1/30
	Game* game = new Game(1000, 1000, 30);

	// simulate cells with 0 delay
	game->simulateGenerations(0);

	// free all game objects
	delete game;

	return 0;
}
