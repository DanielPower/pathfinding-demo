#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "common.h"

class Tile
{
public:
	Tile();
	void setHeight(float height);
	float getHeight();

private:
	uint index;
	float height;
};

#endif
