#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <cinttypes>
#include <cstdint>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class Pixel {
  public:
	Pixel(int x, int y, int activity) : x(x), y(y), activity(activity), neighbors({
			std::make_tuple(x-1,y-1),
			std::make_tuple(x,y-1),
			std::make_tuple(x+1,y-1),
			std::make_tuple(x-1,y),
			std::make_tuple(x+1,y),
			std::make_tuple(x-1,y+1),
			std::make_tuple(x,y+1),
			std::make_tuple(x+1,y+1),
	}) {}
    
	int valid_indices(int x, int y, int width, int height) {
		return (((x > 0) && (x < width)) && ((y > 0) && (y < height)));
	}

	int countNeighbors(std::vector<std::vector<Pixel*>> &graph, int width, int height) {
		int ns = 0;
		for (int i = 0; i < 8; i++) {
			int xc = std::get<0>(this->neighbors[i]);
			int yc = std::get<1>(this->neighbors[i]);
			if (this->valid_indices(xc, yc, width, height)) {
				if (graph[xc][yc]->get_activity())
					ns += 1;
			}
		}
		return ns;
	}
	
	void set_activity(int act) {
		this->activity = act;
	}

	int get_activity() {
		return this->activity;
	}

  private:
	int x;
	int y;
	int activity;
	std::vector<std::tuple<int, int>> neighbors;
};


void compute_next_gen(SDL_Renderer* &renderer, std::vector<std::vector<Pixel*>> &graph, int width, int height, int r, int g, int b) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int neighbors = graph[i][j]->countNeighbors(graph, width, height);
			if (((neighbors < 2) || (neighbors > 3)) && graph[i][j]->get_activity()) {
				graph[i][j]->set_activity(0);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderDrawPoint(renderer, i, j);
			} else if ((neighbors < 4) && (neighbors > 1) && graph[i][j]->get_activity())
				continue;
			else if ((neighbors == 3) && (!graph[i][j]->get_activity())) {
				graph[i][j]->set_activity(1);
				SDL_SetRenderDrawColor(renderer, r, g, b, 0);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}
	SDL_RenderPresent(renderer);
}


int main() {

	srand(time(NULL));

	int width = 1000;
	int height = 1000;
	int dispersal = 20;

	std::vector<std::vector<Pixel*>> graph;

	for (int i = 0; i < width; i++) {
		std::vector<Pixel*> new_vec;
		for (int j = 0; j < height; j++)
			new_vec.push_back(new Pixel(i, j, (rand() % dispersal)));
		graph.push_back(new_vec);
	}

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 128);

	SDL_Event event;

	for (int k = 0; k < width; k++) {
		for (int l = 0; l < height; l++) {
			if (graph[k][l]->get_activity() == 1)
				SDL_RenderDrawPoint(renderer, k, l);
		}
	}
	SDL_RenderPresent(renderer);

	int delay = 0;
	
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	
	while(!(event.type == SDL_QUIT)) {
		SDL_Delay(delay);
		SDL_PollEvent(&event);
		
		if (r > 255) {
			r = r % 255;
			if (g > 255) {
				g = g % 255;
				if (b > 255) {
					r = rand() % 255;
					g = rand() % 255;
					b = rand() % 255;
				} else {
					b += 5;
				}
			} else {
				g += 5;
			}
		} else {
			r += 5;
		}

		// compute next gen
		compute_next_gen(renderer, graph, width, height, r, g, b);
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
			delete graph[i][j];
	}

	return 0;
}
