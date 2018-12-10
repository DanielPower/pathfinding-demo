#include "bfs.h"


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
	for (auto tile :neighbours)
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
		//todo
	}
	return out;
}

tileArray BFS::getClosedList()
{
	return tileArray();
}
