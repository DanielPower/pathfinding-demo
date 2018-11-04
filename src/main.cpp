#include "gui.h"
#include "image.h"
#include "map.h"
#include <iostream>

Gui gui;
Image image;

int main() {
	gui.init();
	Map map = image.load("image.jpg");
	for (uint x=0; x < map.width; x++) {
		for (uint y=0; y<map.height; y++) {
			std::cout << map.map[x][y].height << " ";
		}
		std::cout << std::endl;
	}

	bool isRunning = true;
	while (isRunning) {
		isRunning = gui.update();
	}
}