#include "tile.h"

Tile::Tile(float height)
{
	if (height < 0.2)		sector = 0;
	else if (height > 0.8)	sector = 1;
	else					sector = 2;
}

uint Tile::getSector() {
	return sector;
}

float Tile::getHeight() {
	return height;
}
