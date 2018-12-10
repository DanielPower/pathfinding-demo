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

const float Tile::getHeight() {
	return height;
}

const int Tile::getIndex()
{
	return index;
}

const float Tile::getTravelCost()
{
	return travelCost;
}
