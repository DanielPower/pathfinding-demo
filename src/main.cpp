#include "gui.h"
#include "image.h"

Gui gui;

int main() {
	// Initialize GUI Window
	gui.init();
	Map map = image::load("map.bmp");

	// Update and render GUI
	bool isRunning = true;
	while (isRunning) {
		isRunning = gui.update();
		gui.render();
	}
}