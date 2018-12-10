#include "gui.h"
#include "image.h"
#include "astar.h"
#include "BFS.h"

Gui gui;

int main()
{
	//Create an A* object just so we know we can without blowing stuff up
	Map map = image::load("map.bmp");
	AStar pathFind = AStar(map);
	BFS pathBFS = BFS(map);
	pathBFS.step();
	auto t = map.get(5, 5);
	auto n = map.getLegalNeighbours(t); //again just to show this works

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
