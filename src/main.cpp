#include "common.hpp"
#include "gui.h"
#include "image.h"
#include "astar.h"
#include "bfs.h"

Gui gui;

int main()
{
	//Create an A* object just so we know we can without blowing stuff up
	Map map = Image::load("map.bmp");
	std::shared_ptr<Pathfinding> aStar = std::make_shared<AStar>(map); // FIXME - Causes linter warning, not sure why. Seems to work though.
	std::shared_ptr<Pathfinding> bfs = std::make_shared<BFS>(map);  // FIXME
	auto start = map.get(5, 5);
	auto end = map.get(25, 25);
	bfs->setGoal(start, end);
	bfs->step();
	bfs->step();
	bfs->step();
	auto ol = bfs->getOpenList();
	for (auto tile : bfs->getOpenList())
	{
		std::cout << "Tile : " << tile->getIndex() % map.width << " , " << tile->getIndex() / map.width <<std::endl;
	}

	std::vector<std::shared_ptr<Pathfinding>> pathfinders = {aStar, bfs};

	// Update and render GUI
	bool isRunning = true;
	while (isRunning)
	{
		isRunning = gui.update();
		gui.render();
	}
}
