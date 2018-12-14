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

	//iter neighbours
	for (auto tile : map.getLegalNeighbours(curNode->tile))
	{
		//make node, set parent, calculate hCost
		auto n = std::make_shared<AStarNode>(tile);
		n->parent = curNode;
		n->hCost = calcHScore(n->tile);
		bool isDiag = map.isDiagonal(curNode->tile, n->tile);
		n->gCost = isDiag ? curNode->gCost + 141 : curNode->gCost + 100;
		//check to see if this node already exists on the open list with a lower cost
		if (n->gCost < openLookup[n->tile->getIndex()])
		{
			//JPS scan this new node
			if (!isDiag)
			{
				auto dx = n->tile->getX(map.getWidth()) - curNode->tile->getX(map.getWidth());
				auto dy = n->tile->getY(map.getWidth()) - curNode->tile->getY(map.getWidth());
				cardinalScan(n, dx, dy);
			}
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

//Jump Point Scan for cardinal directions, adds a consecutive series of nodes to the open list
void JPS::cardinalScan(std::shared_ptr<AStarNode> node, int dx, int dy)
{
	//origin node
	const int DELTA_COST = 100;
	//auto curNode = node;
	auto curTile = node->tile;
	bool addNodes = false; //jps terminates when parallel nodes to the path have been added
	auto sector = curTile->getSector();
	uint cost = 0;
	while (true)
	{
		auto ox = curTile->getX(map.getWidth());
		auto oy = curTile->getY(map.getWidth());
		//node we're advancing to with the scan
		auto nextX = ox + dx;
		auto nextY = oy + dy;
		//check termination conditions before calculating jps stuff
		if (map.isOOB(nextX, nextY) || sector != map.get(nextX, nextY)->getSector()) return;
		if (curTile->getIndex() == destination)
		{
			auto endNode = std::make_shared<AStarNode>(curTile);
			Pathfinding::makePath(*endNode); //todo update the method to only take refs
			status = FINISHED;
			return;
		}
		//nodes adjacent to the origin (ie if moving L to R these are the nodes on top and bottom of the origin)
		auto adjX1 = ox + dy;
		auto adjY1 = oy + dx;
		auto adjX2 = ox + -dy;
		auto adjY2 = oy + -dx;
		//nodes adjacent to the advanced node
		auto adjNextX1 = nextX + dy;
		auto adjNextY1 = nextY + dx;
		auto adjNextX2 = nextX + -dy;
		auto adjNextY2 = nextY + -dx;
		cost += DELTA_COST;
		auto nextNode = std::make_shared<AStarNode>(map.get(nextX, nextY));
		nextNode->gCost = cost;
		nextNode->hCost = calcHScore(nextNode->tile);
		nextNode->parent = node; //original node, this will create a discontinuity or "jump" (funny that)
		//check for the potential of parallel nodes
		if (sector != map.get(adjX1, adjY1)->getSector() && sector == map.get(adjNextX1, adjNextY1)->getSector())
		{
			addNodes = true;
			auto adjNode1 = std::make_shared<AStarNode>(map.get(adjNextX1, adjNextY1));
			adjNode1->parent = nextNode;
			adjNode1->gCost = cost;
			adjNode1->hCost = calcHScore(adjNode1->tile);
			openLookup[adjNode1->tile->getIndex()] = adjNode1->gCost;
			openList.push(adjNode1);
		}
		if (sector != map.get(adjX2, adjY2)->getSector() && sector == map.get(adjNextX2, adjNextY2)->getSector())
		{
			addNodes = true;
			auto adjNode2 = std::make_shared<AStarNode>(map.get(adjNextX2, adjNextY2));
			adjNode2->parent = nextNode;
			adjNode2->gCost = cost;
			adjNode2->hCost = calcHScore(adjNode2->tile);
			openLookup[adjNode2->tile->getIndex()] = adjNode2->gCost;
			openList.push(adjNode2);
		}
		if (addNodes) //if we found a parallel node we add the next node to the list and return to pop the lowest score
		{
			openLookup[nextNode->tile->getIndex()] = nextNode->gCost;
			openList.push(nextNode);
			return;
		}
		//no new nodes were added and the path is clear: continue 
		curTile = map.get(nextX, nextY);
	}


}

void JPS::diagScan(std::shared_ptr<AStarNode> node, int dx, int dy)
{
	//origin node
	const int CARD_COST = 100;
	const int DIAG_COST = 141;
	//auto curNode = node;
	auto curTile = node->tile;
	bool addNodes = false; //jps terminates when parallel nodes to the path have been added
	auto sector = curTile->getSector();
	uint cost = 0;
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
	return euclidean(map, t, map.get(destination)) * 100;
}
