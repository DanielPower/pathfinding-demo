#pragma once
#include "pathfinding.h"

class BFS : Pathfinding
{
private:

public:
	std::vector<Tile> getPath() override;
	void step() override;
	std::vector<Tile> getOpenList() override;
	std::vector<Tile> getClosedList() override;
};


