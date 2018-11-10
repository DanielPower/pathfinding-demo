#include "map.h"

Map::Map(uint width, uint height) 
: width(width)
, height(height)
{
	map.resize(width);
	for (uint x=0; x < width; x++)
	{
		map[x].resize(height);
	}
}

std::vector<Tile> Map::operator[](uint index) {
	return map[index];
}