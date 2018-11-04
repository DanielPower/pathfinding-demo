#ifndef MAP_H
#define MAP_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"


class Map
{
public:
	std::vector<std::vector<Tile>> map;
	int width;
	int height;
	Map() = default;
	~Map() = default;
	Tile get(int x, int y);
	sf::Sprite getSprite();
};

#endif
