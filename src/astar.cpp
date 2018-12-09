#include "astar.h"

AStar::AStar(const Map& map) : Pathfinding(map)
{
}

std::vector<Tile> AStar::getPath()
{
	return std::vector<Tile>();
}

void AStar::step()
{
}

std::vector<Tile> AStar::getOpenList()
{
	return std::vector<Tile>();
}

std::vector<Tile> AStar::getClosedList()
{
	return std::vector<Tile>();
}
