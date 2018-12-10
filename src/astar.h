#ifndef ASTAR_H
#define ASTAR_H
#include "map.h"
#include "common.hpp"
#include <vector>
#include "pathfinding.h"


class AStar : public Pathfinding
{
public:
	AStar(const Map& map)
		: Pathfinding(map)
	{
	}

	void step() override;
	tileArray getOpenList() override;
	tileArray getClosedList() override;
};

struct AStarNode : PathNode
{
	uint hCost = 0;
	uint getCost() const { return gCost+hCost; }
};

#endif
