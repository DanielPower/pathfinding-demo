#include "BFS.h"


void BFS::step()
{
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
	if (cListCheck == closedList.end()) return;
	closedList.insert(next.tile->getIndex());
	auto neighbours = map.getLegalNeighbours(next.tile);
	for (auto tile : neighbours)
	{
		PathNode n = PathNode(tile);
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
