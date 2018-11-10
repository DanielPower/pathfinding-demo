#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "common.h"
#include "map.h"
#include "image.h"

class Gui
{
private:
	sf::RenderWindow window;
	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;

public:
	void init();
	bool update();
	void render();
};

#endif