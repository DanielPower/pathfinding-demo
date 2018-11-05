#ifndef GUI_H
#define GUI_H

#include "common.h"
#include <SFML/Graphics.hpp>

class Gui {
private:
	sf::RenderWindow window;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	void init();
	bool update();
	void render();
};

#endif