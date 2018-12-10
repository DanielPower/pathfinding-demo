#include "tile.h"

Tile::Tile() {};

void Tile::setHeight(float _height) {
	height = _height;
}

void Tile::setIndex(uint _index)
{
	index = _index;
}

void Tile::setTravelCost(float cost)
{
	travelCost = cost;
}

const float Tile::getHeight() const
{
	return height;
}

const uint Tile::getIndex() const
{
	return index;
}

const uint Tile::getX(const uint& width) const
{
	return index%width;
}

const uint Tile::getY(const uint& width) const
{
	return index/width;
}

const float Tile::getTravelCost() const
{
	return travelCost;
}
