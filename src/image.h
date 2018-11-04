#ifndef IMAGE_H
#define IMAGE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"

class Image {
public:
	Map load(std::string filename);
	void save(sf::Image, std::string filename);
};

#endif