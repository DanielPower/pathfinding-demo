#ifndef MAP_H
#define MAP_H

#include <vector>
#include "tile.h"
#include "common.hpp"

class Map
{
public:
	std::vector<Tile> map;
	uint width;
	uint height;
	uint size;

	Map(uint width, uint height);
	Tile get(uint x, uint y);
	void set(uint x, uint y, Tile tile);
	int getIndex(uint x, uint y);
};

#endif
