#include "gui.h"

void Gui::init() {
	window.create(sf::VideoMode(1280, 720), "COMP 3200");
}

void Gui::update() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}