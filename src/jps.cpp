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
				int dx = int(n->tile->getX(map.getWidth())) - int(curNode->tile->getX(map.getWidth()));
				int dy = int(n->tile->getY(map.getWidth())) - int(curNode->tile->getY(map.getWidth()));
				//if (dx == 0) continue;
				auto jumpNodes = cardinalScan(n, dx,dy);
				for (auto jump : jumpNodes.get_vec())
				{
					if (jump->gCost > openLookup[n->tile->getIndex()]) continue;
					openLookup[jump->tile->getIndex()] = jump->gCost;
					openList.push(jump);
				}
			}
			//jps diagonal scan
			else
			{
				auto dx = n->tile->getX(map.getWidth()) - curNode->tile->getX(map.getWidth());
				auto dy = n->tile->getY(map.getWidth()) - curNode->tile->getY(map.getWidth());
				auto jumpNodes = diagScan(n, dx, dy);
				for (auto jump : jumpNodes.get_vec())
				{
					if (jump->gCost > openLookup[n->tile->getIndex()]) continue;
					openLookup[jump->tile->getIndex()] = jump->gCost;
					openList.push(jump);
				}
			}
			//add the neighbour if it's still the lowest cost
			//if (n->gCost < openLookup[n->tile->getIndex()]) {
			//	openLookup[n->tile->getIndex()] = n->gCost;
			//	openList.push(n);
			//}
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
aStarQueue JPS::cardinalScan(std::shared_ptr<AStarNode> node, int dx, int dy)
{
	aStarQueue nodeList;
	//origin node
	const int H_COST = 100;
	const int D_COST = 141;
	//auto curNode = node;
	auto curTile = node->tile;
	bool addNodes = false; //jps terminates when parallel nodes to the path have been added
	auto sector = curTile->getSector();
	uint cost = node->gCost;
	while (true)
	{
		auto ox = curTile->getX(map.getWidth());
		auto oy = curTile->getY(map.getWidth());
		//node we're advancing to with the scan
		auto nextX = ox + dx;
		auto nextY = oy + dy;
		//check termination conditions before calculating jps stuff
		if (map.isOOB(nextX, nextY) || sector != map.get(nextX, nextY)->getSector()) {
			return nodeList;
		}
		if (curTile->getIndex() == destination)
		{
			auto endNode = std::make_shared<AStarNode>(curTile);
			endNode->parent = node;
			Pathfinding::makePath(*endNode); //todo update the method to only take refs
			nodeList.push(endNode);
			status = FINISHED;
			return nodeList;
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
		auto nextNode = std::make_shared<AStarNode>(map.get(nextX, nextY));
		nextNode->gCost = cost+H_COST;
		nextNode->hCost = calcHScore(nextNode->tile);
		nextNode->parent = node; //original node, this will create a discontinuity or "jump" (funny that)

		//check for the potential of parallel nodes

		if (!map.isOOB(adjX1, adjY1)&& !map.isOOB(adjNextX1, adjNextY1) && sector != map.get(adjX1, adjY1)->getSector() && sector == map.get(adjNextX1, adjNextY1)->getSector())
		{
			addNodes = true;
			auto adjNode1 = std::make_shared<AStarNode>(map.get(adjNextX1, adjNextY1));
			adjNode1->parent = nextNode;
			adjNode1->gCost = cost+D_COST;
			adjNode1->hCost = calcHScore(adjNode1->tile);
			nodeList.push(adjNode1);
		}
		if (!map.isOOB(adjX2, adjY2) && !map.isOOB(adjNextX2, adjNextY2) && sector != map.get(adjX2, adjY2)->getSector() && sector == map.get(adjNextX2, adjNextY2)->getSector())
		{
			addNodes = true;
			auto adjNode2 = std::make_shared<AStarNode>(map.get(adjNextX2, adjNextY2));
			adjNode2->parent = nextNode;
			adjNode2->gCost = cost+D_COST;
			adjNode2->hCost = calcHScore(adjNode2->tile);
			nodeList.push(adjNode2);
		}
		if (addNodes) //if we found a parallel node we add the next node to the list and return to pop the lowest score
		{
			nodeList.push(nextNode);
			return nodeList;
		}
		//no new nodes were added and the path is clear: continue 
		curTile = map.get(nextX, nextY);
		cost += H_COST;
	}


}

aStarQueue JPS::hScan(std::shared_ptr<AStarNode> node, int dx)
{
	aStarQueue nodeList;
	//origin node
	const int H_COST = 100;
	const int D_COST = 141;
	//auto curNode = node;
	auto curTile = node->tile;
	bool addNodes = false; //jps terminates when parallel nodes to the path have been added
	auto sector = curTile->getSector();
	uint cost = node->gCost;
	while(true)
	{
		auto x0 = curTile->getX(map.getWidth());
		auto y0 = curTile->getY(map.getWidth());
		auto x1 = x0 + dx;
		//check termination conditions before calculating jps stuff
		if (map.isOOB(x1, y0) || sector != map.get(x1, y0)->getSector()) {
			//std::cout << "returning for oob\n";
			return nodeList;
		}
		if (curTile->getIndex() == destination)
		{
			auto endNode = std::make_shared<AStarNode>(curTile);
			endNode->parent = node;
			Pathfinding::makePath(*endNode); //todo update the method to only take refs
			nodeList.push(endNode);
			status = FINISHED;
			return nodeList;
		}
		auto x2 = x1 + dx;
		//(x1,y-1) is blocked but (x2, y-1) is clear: add node
		if (sector != map.get(x1, y0-1)->getSector() && sector == map.get(x2, y0 - 1)->getSector())
		{
			addNodes = true;
			auto btmNode = std::make_shared<AStarNode>(map.get(x2, y0-1));
			btmNode->gCost = cost + D_COST;
			btmNode->hCost = calcHScore(btmNode->tile);
			nodeList.push(btmNode);
		}
		//same as above but this time... above
		if (sector != map.get(x1, y0 + 1)->getSector() && sector == map.get(x2, y0 + 1)->getSector())
		{
			addNodes = true;
			auto topNode = std::make_shared<AStarNode>(map.get(x2, y0 + 1));
			topNode->gCost = cost + D_COST;
			topNode->hCost = calcHScore(topNode->tile);
			nodeList.push(topNode);
		}
		if (addNodes)
		{
			//std::cout << "Adding nodes";
			auto parent = std::make_shared<AStarNode>(map.get(x2, y0));
			parent->gCost = cost + H_COST;
			parent->hCost = calcHScore(parent->tile);
			//set parent here (so we aren't always making nodes
			for (auto n :nodeList.get_vec())
			{
				n->parent = parent;
			}
			nodeList.push(parent);
			return nodeList;
		}
		//simply continue
		cost += H_COST;
		curTile =  map.get(x1, y0);
	}
}

aStarQueue JPS::diagScan(std::shared_ptr<AStarNode> node, int dx, int dy)
{
	aStarQueue nodeList;
	//origin node
	const int CARD_COST = 100;
	const int DIAG_COST = 141;
	//auto curNode = node;
	auto curTile = node->tile;
	bool addNodes = false; //jps terminates when parallel nodes to the path have been added
	auto sector = curTile->getSector();
	uint cost = node->gCost;
	while (true)
	{
		auto ox = curTile->getX(map.getWidth());
		auto oy = curTile->getY(map.getWidth());
		//node we're advancing to with the scan
		auto x1 = ox + dx;
		auto y1 = oy + dy;
		//check termination conditions before calculating jps stuff
		if (map.isOOB(x1, y1) || sector != map.get(x1, y1)->getSector()) return nodeList;
		if (curTile->getIndex() == destination)
		{
			auto endNode = std::make_shared<AStarNode>(curTile);
			endNode->parent = node;
			Pathfinding::makePath(*endNode); //todo update the method to only take refs
			status = FINISHED;
			return nodeList;
		}
		//diagonal path is clear
		cost += DIAG_COST;
		auto nextNode = std::make_shared<AStarNode>(map.get(x1, y1));
		nextNode->gCost = cost;
		nextNode->hCost = calcHScore(nextNode->tile);
		nextNode->parent = node;
		auto x2 = x1 + dx;
		auto y2 = y1 + dy;
		//(x0,y1) is blocked but (x0,y2) is clear: it must be added
		if (sector != map.get(ox, y1)->getSector() && sector == map.get(ox, y1)->getSector())
		{
			addNodes = true;
			auto _n = std::make_shared<AStarNode>(map.get(ox, y2));
			_n->gCost = cost + DIAG_COST; //diag move away from nextNode
			_n->hCost = calcHScore(_n->tile);
			_n->parent = nextNode;
			nodeList.push(_n);
		}
		//(x1,y0) is blocked but (x2,y0) is clear: it must be added
		if (sector != map.get(x1, oy)->getSector() && sector == map.get(x2, oy)->getSector())
		{
			addNodes = true;
			auto _n = std::make_shared<AStarNode>(map.get(ox, y2));
			_n->gCost = cost + DIAG_COST;
			_n->hCost = calcHScore(_n->tile);
			_n->parent = nextNode;
			nodeList.push(_n);
		}
		//no forced neighbours found so far, perform a recursive horizontal scan
		bool hScanFoundNode = false;
		if (nodeList.size() == 0)
		{
			aStarQueue h_nodes;
			h_nodes = cardinalScan(nextNode, dx, 0);
			hScanFoundNode = !h_nodes.empty();
		}

		bool vScanFoundNode = false;
		if (nodeList.size() == 0)
		{
			aStarQueue v_nodes;
			v_nodes = cardinalScan(nextNode, 0, dy);
			vScanFoundNode = !v_nodes.empty();
		}
		if (nodeList.size() != 0 || hScanFoundNode || vScanFoundNode)
		{
			nodeList.push(nextNode);
			return nodeList;
		}
		//we found no forced neighbours and our hor and vert scans returned nothing interesting: continue
		curTile = map.get(x1, y1);
	}
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
