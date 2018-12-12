#include "bfs.h"


void BFS::setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination)
{
	origin = _origin->getIndex();
	destination = _destination->getIndex();
	status = IN_PROGRESS;
	openList.clear();
	closedList.clear();
	openList.push_back(_origin);
}

void BFS::step()
{
	if (status == FINISHED || status == FAILED) return;

	// Open List empty, search has failed
	if (openList.empty())
	{
		status = FAILED;
		return;
	}

	// Pick the next tile from the open list
	auto next = openList.front();
	openList.pop_front();

	// If we've reached the destination, create path
	if (next.tile->getIndex() == destination)
	{
		Pathfinding::makePath(next);
		status = FINISHED;
		return;
	}

	// If tile is in the closed list, skip it
	auto cListCheck = closedList.find(next.tile->getIndex());
	if (cListCheck != closedList.end()) return;

	// Add tile to the closed list
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
		uint x = n % map.getWidth();
		uint y = n / map.getWidth();
		std::shared_ptr<Tile> t = map.get(x, y);
		out.push_back(t);
	}
	return out;
}

std::vector<std::shared_ptr<PathNode>> BFS::getOpenNodes()
{
	std::vector<std::shared_ptr<PathNode>> out;
	for (auto node : openList)
	{
		out.push_back(std::make_shared<PathNode>(node));
	}
	return out;
}
