#include "astar.h"

void AStar::step()
{
	if (status == FINISHED || status == FAILED) return;
	// Open List empty, search has failed
	if (openList.empty())
	{
		status = FAILED;
		return;
	}
	// Pick the next tile from the open list
	auto next = openList.top();
	openList.pop();

	// If we've reached the destination, create path
	if (next->tile->getIndex() == destination)
	{
		Pathfinding::makePath(*next); //todo update the method to only take refs
		status = FINISHED;
		return;
	}

	// If tile is in the clost list, skip it
	auto cListCheck = closedList.find(next->tile->getIndex());
	if (cListCheck != closedList.end()) return;

	// Add tile to the closed list
	uint idx = next->tile->getIndex();
	uint cost = next->getCost();
	closedList[idx] = cost;

	auto neighbours = map.getLegalNeighbours(next->tile);
	for (auto tile : neighbours)
	{
		auto n = std::make_shared<AStarNode>(tile);
		//todo fix heuristic
		n->hCost = calcHScore(n->tile);
		n->gCost = (n->parent == nullptr) ? 100 : n->parent->gCost + 100;
		auto cListCheck = closedList.find(n->tile->getIndex());
		if (cListCheck != closedList.end()) continue;
		n->parent = next;
		openList.push(n);
	}
}

tileArray AStar::getOpenList()
{
	tileArray out;
	for (auto n : openList.get_vec())
	{
		out.push_back(n->tile);
	}
	return out;
}

tileArray AStar::getClosedList()
{
	tileArray out;
	for (auto pair : closedList)
	{
		auto n = pair.first;
		uint x = n % map.width;
		uint y = n / map.width;
		std::shared_ptr<Tile> t = map.get(x, y);
		out.push_back(t);
	}
	return out;
}

void AStar::setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination)
{
	origin = _origin->getIndex();
	destination = _destination->getIndex();
	auto og = std::make_shared<AStarNode>(_origin);
	openList.push(og);
}

uint AStar::calcHScore(const std::shared_ptr<Tile> t)
{
	//todo pick between heuristics
	return uint(euclidean(map, t, map.map[destination]));
}


