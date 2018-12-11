#include "bfs.h"


void BFS::setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination)
{
	origin = _origin->getIndex();
	destination = _destination->getIndex();
	openList.push_back(_origin);
}

void BFS::step()
{
	if (status == FINISHED || status == FAILED) return;
	if (openList.empty())
	{
		status = FAILED;
		return;
	}
	auto next = openList.front();
	openList.pop_front();

	if (next.tile->getIndex() == destination)
	{
		Pathfinding::makePath(next);
		status = FINISHED;
		return;
	}
	auto cListCheck = closedList.find(next.tile->getIndex());
	if (cListCheck != closedList.end()) return; //item is already in closed list
	closedList.insert(next.tile->getIndex());
	auto neighbours = map.getLegalNeighbours(next.tile);
	for (auto tile : neighbours)
	{
		PathNode n = PathNode(tile);
		auto cListCheck = closedList.find(n.tile->getIndex());
		if (cListCheck != closedList.end()) continue;
		n.parent = std::make_shared<PathNode>(next);
		openList.push_back(n);
	}
}

tileArray BFS::getOpenList()
{
	tileArray out;
	for (auto n : openList)
	{
		out.push_back(n.tile);
	}
	return out;
}

tileArray BFS::getClosedList()
{
	tileArray out;
	for (auto n : closedList)
	{
		uint x = n % map.width;
		uint y = n / map.width;
		std::shared_ptr<Tile> t = map.get(x, y);
		out.push_back(t);
	}
	return out;
}
