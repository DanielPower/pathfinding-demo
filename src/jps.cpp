#include "jps.h"


void JPS::setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination)
{
	origin = _origin->getIndex();
	destination = _destination->getIndex();
	status = IN_PROGRESS;
	openList.get_vec().clear();
	openLookup = std::vector<uint>(map.getWidth()*map.getHeight(), UINT_MAX);
	closedList.clear();

	auto og = std::make_shared<AStarNode>(_origin);
	og->gCost = 0;
	openList.push(og);
}

void JPS::step()
{
	if (status == FINISHED || status == FAILED) return;

	// Open List empty, search has failed
	if (openList.empty())
	{
		status = FAILED;
		return;
	}

	// Pick the next tile from the open list
	auto curNode = openList.top();
	openList.pop();

	// If we've reached the destination, create path
	if (curNode->tile->getIndex() == destination)
	{
		Pathfinding::makePath(*curNode); //todo update the method to only take refs
		status = FINISHED;
		return;
	}

	// If tile is in the closed list, skip it
	auto cListCheck = closedList.find(curNode->tile->getIndex());
	if (cListCheck != closedList.end())
	{
		return;
	}

	// Add tile to the closed list
	uint idx = curNode->tile->getIndex();
	uint cost = curNode->getCost();
	closedList[idx] = cost;
	// iter neighbours
	for (auto tile : map.getLegalNeighbours(curNode->tile))
	{
		auto n = std::make_shared<AStarNode>(tile);
		n->parent = curNode;
		n->hCost = calcHScore(n->tile);
		n->gCost = map.isDiagonal(curNode->tile, n->tile) ? curNode->gCost + 141 : curNode->gCost + 100;
		if (n->gCost < openLookup[n->tile->getIndex()])
		{
			openLookup[n->tile->getIndex()] = n->gCost;
			openList.push(n);
		}
	}
}

tileArray JPS::getOpenList()
{
	tileArray out;
	for (auto n : openList.get_vec())
	{
		out.push_back(n->tile);
	}
	return out;
}

tileArray JPS::getClosedList()
{
	tileArray out;
	for (auto pair : closedList)
	{
		auto n = pair.first;
		uint x = n % map.getWidth();
		uint y = n / map.getWidth();
		std::shared_ptr<Tile> t = map.get(x, y);
		out.push_back(t);
	}
	return out;
}

std::vector<std::shared_ptr<PathNode>> JPS::getOpenNodes()
{
	std::vector<std::shared_ptr<PathNode>> out;
	for (auto node : openList.get_vec())
	{
		out.push_back(node);
	}
	return out;
}

float JPS::calcHScore(const std::shared_ptr<Tile>& t)
{
	//todo pick between heuristics
	return euclidean(map, t, map.get(destination))*100;
}
