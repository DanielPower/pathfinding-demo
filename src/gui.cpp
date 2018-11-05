#include "gui.h"

void Gui::init() {
	window.create(sf::VideoMode(1280, 720), "COMP 3200");
}

bool Gui::update() {
	if (window.isOpen()) {
		// Events
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		return true;
	}
	
	return false;
}

void Gui::render() {
	// Rendering
	window.clear(sf::Color::White);
	window.draw(sprite);
	window.display();
}