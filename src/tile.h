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
	void setTravelCost(float cost);
	const float getHeight();
	const uint getIndex();
	const float getTravelCost();
private:
	uint index;
	float height;
	float travelCost;
};

typedef std::vector<std::shared_ptr<Tile>> tileArray;

#endif
