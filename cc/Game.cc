#include "Game.h"

Game::Game(int width, int height, int dispersal) : width(width), height(height), dispersal(dispersal) {
	srand(time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	for (int i = 0; i < width; i++) {
		std::vector<Pixel*> new_vec;
		int r = 0;
		for (int j = 0; j < height; j++) {
			r = rand() % dispersal;
			new_vec.push_back(new Pixel(i, j, r));
			if (r == 1)
				SDL_RenderDrawPoint(this->renderer, i, j);
		}
		this->graph.push_back(new_vec);
	}

	SDL_RenderPresent(this->renderer);
}

Game::~Game() {
	for (auto pixelarray : this->getGraph()) {
		for (auto pixel : pixelarray)
			delete pixel;
	}
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
}

int Game::running(SDL_Event &event) {
	return !(event.type == SDL_QUIT);
}

std::vector<std::vector<Pixel*>> Game::getGraph() {
	return this->graph;
}

void Game::simulateGenerations(int delay) {
	SDL_Event event;
	while (this->running(event)) {
		SDL_Delay(delay);
		SDL_PollEvent(&event);
		this->computeNextGeneration(this->graph);
	}
}

void Game::computeNextGeneration(std::vector<std::vector<Pixel*>> &newGraph) {
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	for (int i = 0; i < this->getWidth(); i++) {
		for (int j = 0; j < this->getHeight(); j++) {
			int neighbors = newGraph[i][j]->countNeighbors(newGraph, this->getWidth(), this->getHeight());
			if (((neighbors < 2) || (neighbors > 3)) && newGraph[i][j]->getActivity()) {
				newGraph[i][j]->setActivity(0);
				SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 0);
				SDL_RenderDrawPoint(this->getRenderer(), i, j);
			} else if ((neighbors < 4) && (neighbors > 1) && newGraph[i][j]->getActivity())
				continue;
			else if ((neighbors == 3) && (!newGraph[i][j]->getActivity())) {
				newGraph[i][j]->setActivity(1);
				SDL_SetRenderDrawColor(this->getRenderer(), r, g, b, 0);
				SDL_RenderDrawPoint(this->getRenderer(), i, j);
			}
		}
	}
	SDL_RenderPresent(this->getRenderer());
}

int Game::getWidth() {
	return this->width;
}

int Game::getHeight() {
	return this->height;
}

SDL_Renderer* Game::getRenderer() {
	return this->renderer;
}
