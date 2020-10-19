#include "Pixel.h"

Pixel::Pixel(int x, int y, int activity) : x(x), y(y), activity(activity), neighbors({
	std::make_tuple(x-1,y-1), std::make_tuple(x,y-1),
	std::make_tuple(x+1,y-1), std::make_tuple(x-1,y),
	std::make_tuple(x+1,y), std::make_tuple(x-1,y+1),
	std::make_tuple(x,y+1), std::make_tuple(x+1,y+1),
}){}

Pixel::~Pixel() {}

int Pixel::validIndices(int x, int y, int width, int height) {
	return (((x > 0) && (x < width)) && ((y > 0) && (y < height)));
}

int Pixel::countNeighbors(std::vector<std::vector<Pixel*>> &graph, int width, int height) {
	int ns = 0;
	for (int i = 0; i < 8; i++) {
		int xc = std::get<0>(this->neighbors[i]);
		int yc = std::get<1>(this->neighbors[i]);
		if (this->validIndices(xc, yc, width, height)) {
			if (graph[xc][yc]->getActivity())
				ns += 1;
		}
	}
	return ns;
}
	
void Pixel::setActivity(int act) {
	this->activity = act;
}

int Pixel::getActivity() {
	return this->activity;
}
