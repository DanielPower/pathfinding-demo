#include "BFS.h"


void BFS::step()
{
	if (openList.empty())
	{
		status = FAILED;
		return;
	}
	auto next = openList.front();
	openList.pop();
	if (next.tile.getIndex() == destination)
	{
		Pathfinding::makePath(next);
		status = FINISHED;
		return;
	}
	auto cListCheck = closedList.find(next.tile.getIndex());
	if (cListCheck == closedList.end()) return;
	closedList.insert(next.tile.getIndex());
	//todo add legal neighbours to open list

}

tileArray BFS::getOpenList()
{
	return tileArray();
}

tileArray BFS::getClosedList()
{
	return tileArray();
}
