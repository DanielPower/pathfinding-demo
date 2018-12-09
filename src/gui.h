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
	sf::View view;
	float zoom;
	int prevMouseX;
	int prevMouseY;
	int deltaMouseX;
	int deltaMouseY;

public:
	void init();
	bool update();
	void render();
};

#endif
