#ifndef MAP_H
#define MAP_H
#include <vector>

class Map
{
public:
	std::vector<std::vector<float>> map;
	int width;
	int height;
	Map() = default;
	~Map() = default;
	float get(int x, int y);
};

#endif
