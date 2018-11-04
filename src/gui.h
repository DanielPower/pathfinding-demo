#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

class Gui {
private:
	sf::RenderWindow window;
	sf::Sprite sprite;

public:
	void init();
	bool update();
};

#endif