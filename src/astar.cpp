#include "astar.h"

void AStar::step()
{
}

tileArray AStar::getOpenList()
{
	return tileArray();
}

tileArray AStar::getClosedList()
{
	return tileArray();
}

void AStar::setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination)
{
	origin = _origin->getIndex();
	destination = _destination->getIndex();
	//todo add to open list
}
