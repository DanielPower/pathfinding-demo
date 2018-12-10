#pragma once
#include "pathfinding.h"
#include <queue>
#include <unordered_set>


class BFS : Pathfinding
{
private:
	std::queue<PathNode> openList;
	std::unordered_set<uint> closedList; //closed list can be cached off Tile.index
public:
	explicit BFS(const Map& map)
		: Pathfinding(map)
	{
	}

	void step() override;
	tileArray getOpenList() override;
	tileArray getClosedList() override;
};


