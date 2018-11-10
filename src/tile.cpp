#include "tile.h"

Tile::Tile(float height)
: height(height)
{}

sf::Color Tile::getColor()
{
	sf::Color clr;
	if (height < .2) clr = sf::Color::Blue;
	else if (height > .8) clr = sf::Color(127, 127, 127);
	else clr = sf::Color::Green;
	return clr;
}
