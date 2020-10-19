#ifndef GAME_HPP_
#define GAME_HPP_
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Pixel.h"
class Game {
  public:
  	Game(int width, int height, int dispersal);
	~Game();
	int running(SDL_Event &event);
	int getWidth();
	int getHeight();
	SDL_Renderer* getRenderer();
	std::vector<std::vector<Pixel*>> getGraph();
	void simulateGenerations(int delay);
	void computeNextGeneration(std::vector<std::vector<Pixel*>> &newGraph);
  private:
  	int width;
	int height;
	int dispersal;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	std::vector<std::vector<Pixel*>> graph;
};
#endif // GAME_HPP_
