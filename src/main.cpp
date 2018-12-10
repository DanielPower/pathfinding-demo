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
	auto start = map.get(5, 5);
	auto end = map.get(25, 25);
	pathBFS.setGoal(start, end);
	pathBFS.step();
	pathBFS.step();
	pathBFS.step();
	auto ol = pathBFS.getOpenList();
	for (auto tile : pathBFS.getOpenList())
	{
		std::cout << "Tile : " << tile->getIndex() % map.width << " , " << tile->getIndex() / map.width <<std::endl;
	}

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
