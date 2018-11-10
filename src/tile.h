#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "common.h"

class Tile
{
public:
	float height;
	float food;
	float wood;
	float ore;
	Tile() {};
	Tile(float height);
	sf::Color getColor();
};

#endif
