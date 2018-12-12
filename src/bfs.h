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

	void setGoal(std::shared_ptr<Tile> _origin, std::shared_ptr<Tile> _destination) override;
	void step() override;
	tileArray getOpenList() override;
	tileArray getClosedList() override;
	std::vector<std::shared_ptr<PathNode>> getOpenNodes() override;
};
