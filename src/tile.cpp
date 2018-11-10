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

float Tile::getHeight() {
	return height;
}

int Tile::getIndex()
{
	return index;
}

float Tile::getTravelCost()
{
	return travelCost;
}
