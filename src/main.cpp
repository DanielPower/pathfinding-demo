#include "common.hpp"
#include "gui.h"
#include "image.h"
#include "astar.h"
#include "bfs.h"

Gui gui;

int main()
{
	// Create an A* object just so we know we can without blowing stuff up
	Map map = Image::load("map.bmp");
	std::shared_ptr<Pathfinding> aStar = std::make_shared<AStar>(map); // FIXME - Causes linter warning, not sure why. Seems to work though.
	std::shared_ptr<Pathfinding> bfs = std::make_shared<BFS>(map);  // FIXME
	bfs->step();
	auto t = map.get(5, 5);
	auto n = map.getLegalNeighbours(t); // again just to show this works

	std::vector<std::shared_ptr<Pathfinding>> pathfinders = {aStar, bfs};

	// Update and render GUI
	bool isRunning = true;
	while (isRunning)
	{
		isRunning = gui.update();
		gui.render();
	}
}
