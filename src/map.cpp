#include "map.h"

Map::Map(uint width, uint height) 
: width(width)
, height(height)
{
	size = width*height;
	map.resize(width*height);
}

int Map::getIndex(uint x, uint y)
{
	return y * height + x;
}

Tile Map::get(uint x, uint y)
{
	return map[getIndex(x, y)];
}

void Map::set(uint x, uint y, Tile tile)
{
	map[getIndex(x, y)] = tile;
}