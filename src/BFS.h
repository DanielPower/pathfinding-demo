#pragma once
#include "pathfinding.h"
#include <queue>
#include <unordered_set>

/*
 * Because BFS uses a simple queue structure, we don't even need to use the pathfinding node class
 * We can just use a queue of tiles directly
 */

class BFS : Pathfinding
{
private:
	std::queue<Tile&> openList;
	std::unordered_set<uint> closedList; //open list can be cached off Tile.index
public:
	std::vector<Tile&> getPath() override;
	void step() override;
	std::vector<Tile&> getOpenList() override;
	std::vector<Tile&> getClosedList() override;
};


