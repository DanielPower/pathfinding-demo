#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
public:
	float height;
	float food;
	float wood;
	float ore;
	Tile() {};
	Tile(float height)
		: height(height) {};
	sf::Color getColor();
};

#endif
