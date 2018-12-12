#ifndef ASTAR_H
#define ASTAR_H
#include "map.h"
#include "common.hpp"
#include <vector>
#include "pathfinding.h"
#include <queue>
#include <unordered_map>
#include "pqueue.hpp"


struct AStarNode : PathNode
{
	uint hCost = 0;
	explicit AStarNode(const std::shared_ptr<Tile>& t)
		: PathNode(t)
	{
	}
	uint getCost() const { return gCost + hCost; }
};

class AStar : public Pathfinding
{
public:
	//std::priority_queue<PathNode> openList;
	pQueue<std::shared_ptr<AStarNode>> openList;
	std::unordered_map<uint, uint> closedList; //tile.index -> gCost
	AStar(const Map& map)
		: Pathfinding(map)
	{
	}
	void step() override;
	tileArray getOpenList() override;
	tileArray getClosedList() override;
	void setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination) override;
};



#endif
