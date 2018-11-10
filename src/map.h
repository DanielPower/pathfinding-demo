#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tile.h"
#include "common.h"

class Map
{
public:
	std::vector<Tile> map;
	uint width;
	uint height;

	Map(uint width, uint height);
	Tile get(uint x, uint y);
	int getIndex(uint x, uint y);
};

#endif
