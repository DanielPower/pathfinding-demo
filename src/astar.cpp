#include "astar.h"

void AStar::step()
{
}

tileArray AStar::getOpenList()
{
	tileArray out;
	//for (auto n : openList)
	//{
	//	out.push_back(n.tile);
	//}
	return out;
}

tileArray AStar::getClosedList()
{
	return tileArray();
}

void AStar::setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination)
{
	origin = _origin->getIndex();
	destination = _destination->getIndex();
	auto og = std::make_shared<AStarNode>(_origin);
	openList.push(*og);
}

