#include "gui.h"
#include "image.h"

Gui gui;

int main()
{
	// Initialize GUI Window
	gui.init();

	// Update and render GUI
	bool isRunning = true;
	while (isRunning)
	{
		isRunning = gui.update();
		gui.render();
	}
}