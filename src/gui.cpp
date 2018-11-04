#include "gui.h"

void Gui::init() {
	window.create(sf::VideoMode(1280, 720), "COMP 3200");
	sf::Texture image;
	image.loadFromFile("image.jpg");
	sf::Sprite sprite(image);

}

bool Gui::update() {
	// Events
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			return false;
		}
	}

	// Rendering
	window.clear();
	window.draw(sprite);
	window.display();

	return true;
}