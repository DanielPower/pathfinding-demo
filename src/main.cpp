#include "common.hpp"
#include "gui.h"
#include "image.h"
#include "astar.h"
#include "bfs.h"

Gui gui;

int main()
{
	// Update and render GUI
	bool isRunning = true;
	while (isRunning)
	{
		isRunning = gui.update();
		gui.render();
	}
}
