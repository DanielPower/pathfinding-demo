#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

class Gui {
private:
	sf::Window window;

public:
	void init();
	void update();
};

#endif