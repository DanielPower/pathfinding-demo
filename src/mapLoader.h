#ifndef IMAGE_H
#define IMAGE_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "map.h"
#include "common.hpp"

namespace MapLoader
{
	Map fromImage(std::string filename);
	Map fromText(std::string filename);
	void save(sf::Image, std::string filename);
};

#endif
