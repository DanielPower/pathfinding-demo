#ifndef ASTAR_H
#define ASTAR_H
#include "map.h"
#include "common.h"
#include <vector>
#include <queue>
#include "pathfinding.h"
class AStar : public Pathfinding
{
public:
	AStar(const Map& map);
	std::vector<Tile> getPath() override;
	void step() override;
	std::vector<Tile> getOpenList() override;
	std::vector<Tile> getClosedList() override;
	std::vector<Tile> vanilla(Tile start, Tile end);
};

struct AStarNode : PathNode
{
	uint hCost = 0;
	uint getCost() const { return gCost+hCost; }
};

#endif