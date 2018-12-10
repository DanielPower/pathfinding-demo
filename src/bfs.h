#pragma once
#include "pathfinding.h"
#include <deque>
#include <unordered_set>


class BFS : public Pathfinding
{
private:
	std::deque<PathNode> openList;
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
