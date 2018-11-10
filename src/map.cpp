#include "map.h"

Map::Map(uint width, uint height) 
: width(width)
, height(height)
{
	map.resize(width*height);
}

int Map::getIndex(uint x, uint y)
{
	return y * height + x;
}