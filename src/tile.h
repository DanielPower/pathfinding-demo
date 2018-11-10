#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "common.h"

class Tile
{
public:
	Tile();
	void setHeight(float height);
	void setIndex(uint index);
	float getHeight();
	int getIndex();
	float getTravelCost();
private:
	uint index;
	float height;
	float travelCost;
};

#endif
