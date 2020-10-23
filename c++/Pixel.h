#ifndef PIXEL_HPP_
#define PIXEL_HPP_
#include <tuple>
#include <vector>
class Pixel {
  public:
  	Pixel(int x, int y, int activity);
	~Pixel();
	int validIndices(int x, int y, int width, int height);
	int countNeighbors(std::vector<std::vector<Pixel*>> &graph, int width, int height);
	void setActivity(int activity);
	int getActivity();
  private:
	int x;
	int y;
	int activity;
	std::vector<std::tuple<int, int>> neighbors;
};
#endif // PIXEL_HPP_
