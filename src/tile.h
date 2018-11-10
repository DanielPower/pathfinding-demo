#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "common.h"

class Tile
{
public:
	Tile(float height);
	uint getSector();
	float getHeight();

private:
	uint sector;
	float height;
};

#endif
