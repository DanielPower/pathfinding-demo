#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tile.h"

class Map
{
public:
	std::vector<std::vector<Tile>> map;
	int width;
	int height;
	
	Map(uint width, uint height);
	Tile get(uint x, uint y);
};

#endif
