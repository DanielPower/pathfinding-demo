#include "BFS.h"

std::vector<Tile&> BFS::getPath()
{
	return std::vector<Tile&>();
}

void BFS::step()
{
	if (openList.empty())
	{
		status = FAILED;
		return;
	}
	auto next = openList.front();
	openList.pop();
	if (next.getIndex() == destination)
	{
		status = FINISHED;
		return;
	}

}

std::vector<Tile&> BFS::getOpenList()
{
	return std::vector<Tile&>();
}

std::vector<Tile&> BFS::getClosedList()
{
	return std::vector<Tile&>();
}
